#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  SOCKET ;
typedef  char* LPSTR ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GetSystemDirectoryW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ GetTickCount () ; 
 scalar_t__ HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  LOG_FILE ; 
 int /*<<< orphan*/  LogEvent (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SendQuote (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int rand () ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  szFilePath ; 
 int /*<<< orphan*/  wcscat (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL
RetrieveQuote(SOCKET sock)
{
    HANDLE hFile;
    WCHAR szFullPath[MAX_PATH + 20];
    DWORD dwBytesRead;
    LPSTR lpQuotes;
    LPSTR lpStr;
    INT quoteNum;
    INT NumQuotes = 0;
    INT i;

    if(!GetSystemDirectoryW(szFullPath, MAX_PATH))
    {
        LogEvent(L"QOTD: Getting system path failed", GetLastError(), 0, LOG_FILE);
        return FALSE;
    }
    wcscat(szFullPath, szFilePath);


    LogEvent(L"QOTD: Opening quotes file", 0, 0, LOG_FILE);
    hFile = CreateFileW(szFullPath,
                        GENERIC_READ,
                        0,
                        NULL,
                        OPEN_EXISTING,
                        FILE_ATTRIBUTE_NORMAL,
                        NULL);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        LogEvent(L"QOTD: Error opening quotes file", GetLastError(), 0, LOG_FILE);
    }
    else
    {
        DWORD dwSize = GetFileSize(hFile, NULL);
        lpQuotes = (LPSTR)HeapAlloc(GetProcessHeap(), 0, dwSize + 1);
        if (!lpQuotes) 
        {
            CloseHandle(hFile);
            return FALSE;
        }

        ReadFile(hFile,
                 lpQuotes,
                 dwSize,
                 &dwBytesRead,
                 NULL);
        CloseHandle(hFile);

        lpQuotes[dwSize] = 0;

        if (dwBytesRead != dwSize)
        {
            HeapFree(GetProcessHeap(), 0, lpQuotes);
            return FALSE;
        }

        lpStr = lpQuotes;
        while (*lpStr)
        {
            if (*lpStr == '%')
                NumQuotes++;
            lpStr++;
        }

        /* pick a random quote */
        srand((unsigned int) GetTickCount());
        quoteNum = rand() % NumQuotes;

        /* retrieve the full quote */
        lpStr = lpQuotes;
        for (i = 1; i <= quoteNum; i++)
        {
            /* move past preceding quote */
            lpStr++;

            if (i == quoteNum)
            {
                LPSTR lpStart = lpStr;

                while (*lpStr != '%' && *lpStr != '\0')
                    lpStr++;

                *lpStr = 0;

                /* send the quote */
                if (!SendQuote(sock, lpStart))
                    LogEvent(L"QOTD: Error sending data", 0, 0, LOG_FILE);
                break;
            }
            else
            {
                while (*lpStr != '%' && *lpStr != '\0')
                    lpStr++;

                /* move past % and RN */
                lpStr += 2;
            }
        }

        HeapFree(GetProcessHeap(), 0, lpQuotes);
        return TRUE;
    }

    return FALSE;
}