#include<windows.h>
#include<stdio.h>

LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

HWND createEditBox(HWND);
HWND createButton1(HWND);
HWND createButton2(HWND);
HWND createButton3(HWND);

int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPSTR lpCmdLine,int nCmdShow)
{
	MSG msg;
	HWND hwnd;
	WNDCLASSEX wndclass;

	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.cbClsExtra=0;
	wndclass.cbWndExtra=0;
	wndclass.lpszClassName = TEXT("Class Project");
	wndclass.lpszMenuName =  NULL;
	wndclass.lpfnWndProc=WndProc;
	wndclass.hInstance=hInstance;
	wndclass.hbrBackground=(HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon=LoadIcon(hInstance,TEXT("IDI_ICON"));
	wndclass.hIconSm=LoadIcon(hInstance,TEXT("IDI_ICON"));
	wndclass.hCursor=LoadIcon(hInstance,TEXT("IDI_ICON"));

	RegisterClassEx(&wndclass);

	hwnd = CreateWindow
		(
			TEXT("Class Project"),
			TEXT("Project 1-Counting Words & Character"),
			WS_OVERLAPPEDWINDOW,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			NULL,
			NULL,
			hInstance,
			NULL
		);

	if(!hwnd)
	{
		MessageBox(hwnd,TEXT("Windows not get created"),TEXT("Error"),MB_OK);
		exit(0);
	}

	ShowWindow(hwnd,nCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);

}//WinMain

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{ 
	static HWND hWndEditBox,hwndButton1,hwndButton2,hwndButton3;
	TCHAR wgetevent[256],wfilename[256],buff[66];
	DWORD noofbytegetread;
	char getevent[256],filename[256],str[256];
  
	switch (msg)
	{
		case WM_CREATE:

			hWndEditBox = createEditBox(hWnd);
			hwndButton1 = createButton1(hWnd);
			hwndButton2 = createButton2(hWnd);
			hwndButton3 = createButton3(hWnd);

			break;
	
		case WM_COMMAND:
	
			GetWindowText((HWND)lParam,wgetevent,-1); //To Know which Button get Pressed
			wcstombs(getevent, wgetevent, wcslen(wgetevent) + 1); //To convert wide char string to single char string
			
			if(strcmp("Count Word",getevent)==0)
			{
				GetWindowText(hWndEditBox,wfilename,-1); //To get text from textbox
				wcstombs(filename,wfilename, wcslen(wfilename) + 1);
		
				OFSTRUCT lpofstructwgetevent;
				
				HFILE hfile=OpenFile(filename,&lpofstructwgetevent,OF_READ);
				
				if(hfile == -1)
				{
					wsprintf(buff,TEXT("File %s is not present."),wfilename);
					MessageBox(hWnd,buff,L"ERROR",MB_OK);
				}
				else
				{
					HANDLE handel = CreateFile(wfilename, FILE_READ_DATA, FILE_SHARE_READ,NULL, OPEN_ALWAYS, 0, NULL);
				
					int wcnt=0;
			
					do
					{
						ReadFile(handel,str,256,&noofbytegetread,NULL);
					
						for(int i=0;i<noofbytegetread;i++)
							if(str[i]==' ')
								wcnt++;
					}while(noofbytegetread!=0);
						
					wsprintf(buff,TEXT("%s file have %d words."),wfilename,wcnt);
					MessageBox(hWnd,buff,TEXT("Info"),MB_OK );
				}
			}	
			
			if(strcmp("Count Char",getevent)==0)
			{
				GetWindowText(hWndEditBox,wfilename,-1); //To get text from textbox
				wcstombs(filename,wfilename, wcslen(wfilename) + 1);
				
				OFSTRUCT lpofstructwgetevent;
				
				HFILE hfile=OpenFile(filename,&lpofstructwgetevent,OF_READ);
		
				if(hfile == -1)
				{
					wsprintf(buff,TEXT("File %s is not present."),wfilename);
					MessageBox(hWnd,buff,L"ERROR",MB_OK);
					
				}
				else
				{
					HANDLE handel =CreateFile(wfilename, FILE_READ_DATA, FILE_SHARE_READ,NULL, OPEN_ALWAYS, 0, NULL);
					
					int ccnt=0;
					
					do
					{
						ReadFile(handel,str,256,&noofbytegetread,NULL);
						ccnt+=noofbytegetread;
					}
					while(noofbytegetread!=0);
						
					wsprintf(buff,TEXT("%s file have %d char."),wfilename,ccnt);
					MessageBox(hWnd,buff,TEXT("Info"),MB_OK);
				}
			}

			if(strcmp("Close",getevent)==0)
			{
				PostQuitMessage(0);
			}	
			break;
  
		case WM_DESTROY:
			PostQuitMessage(0);
			break;
	}//switch
	
	return DefWindowProc(hWnd, msg, wParam, lParam);

}//WndProc

HWND createEditBox(HWND hWnd)
{
		return (			CreateWindow( 
		TEXT("EDIT"),  
		NULL,  
	    WS_VISIBLE | WS_CHILD ,
	    100,        
		20,         
		140,	    
	    20,        
		hWnd,     
	    NULL,      
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
	    NULL)
		);     
}

HWND createButton1(HWND hWnd)
{
		return (
		CreateWindow( 
		TEXT("BUTTON"),
		L"Count Word", 
	    WS_TABSTOP | WS_VISIBLE | WS_CHILD ,  
	    10,         
		100,       
		100,	   
	    50,        
		hWnd,     
	    NULL,     
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
	    NULL)
		);      
}


HWND createButton2(HWND hWnd)
{
		return (			CreateWindow( 
		TEXT("BUTTON"),
		L"Count Char", 
	    WS_TABSTOP | WS_VISIBLE | WS_CHILD ,  
	    110,         
		100,       
		100,	   
	    50,        
		hWnd,     
	    NULL,     
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
	    NULL)
		);      
}
HWND createButton3(HWND hWnd)
{
		return (			CreateWindow( 
		TEXT("BUTTON"),
		L"Close", 
	    WS_TABSTOP | WS_VISIBLE | WS_CHILD ,  
	    210,         
		100,       
		100,	   
	    50,        
		hWnd,     
	    NULL,     
		(HINSTANCE)GetWindowLong(hWnd, GWL_HINSTANCE), 
	    NULL)
		);      
}
