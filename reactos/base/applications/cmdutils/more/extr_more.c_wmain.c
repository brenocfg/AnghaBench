#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int /*<<< orphan*/  member_1; TYPE_1__* member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  member_0; } ;
typedef  char TCHAR ;
typedef  int /*<<< orphan*/ * PWCHAR ;
typedef  int /*<<< orphan*/ * PVOID ;
typedef  scalar_t__ ENCODING ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ CON_SCREEN ;
typedef  TYPE_2__ CON_PAGER ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAYSIZE (char*) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ConPuts (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ConPutsPaging (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConStreamInit (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConStreamSetOSHandle (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ConWritePaging (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ CreateFileW (char*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ENCODING_ANSI ; 
 scalar_t__ ENCODING_UTF16BE ; 
 scalar_t__ ENCODING_UTF16LE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int FILE_SHARE_READ ; 
 int FILE_SHARE_WRITE ; 
 int /*<<< orphan*/  FileCacheBufferSize ; 
 scalar_t__ FileGetString (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  FlushConsoleInputBuffer (scalar_t__) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetFileSize (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFullPathNameW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 void* GetStdHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDS_FILE_ACCESS ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 int /*<<< orphan*/  INVALID_CP ; 
 scalar_t__ INVALID_FILE_SIZE ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  IsDataUnicode (int /*<<< orphan*/ *,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PagePrompt ; 
 scalar_t__ ReadFile (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_ERROR_HANDLE ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  STD_OUTPUT_HANDLE ; 
 int /*<<< orphan*/  SetFilePointer (scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StdErr ; 
 int /*<<< orphan*/  StdIn ; 
 int /*<<< orphan*/  StdOut ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  UTF8Text ; 
 scalar_t__ dwFileSize ; 
 scalar_t__ dwSumReadBytes ; 
 scalar_t__ dwSumReadChars ; 
 scalar_t__ hFile ; 
 scalar_t__ hKeyboard ; 
 scalar_t__ hStdIn ; 
 void* hStdOut ; 
 scalar_t__ wcscmp (int /*<<< orphan*/ *,char*) ; 

int wmain(int argc, WCHAR* argv[])
{
    // FIXME this stuff!
    CON_SCREEN Screen = {StdOut};
    CON_PAGER Pager = {&Screen, 0};

    int i;

    BOOL bRet, bContinue;

    ENCODING Encoding;
    DWORD SkipBytes = 0;

#define FileCacheBufferSize 4096
    PVOID FileCacheBuffer = NULL;
    PWCHAR StringBuffer = NULL;
    DWORD StringBufferLength = 0;
    DWORD dwReadBytes, dwReadChars;

    TCHAR szFullPath[MAX_PATH];

    hStdIn = GetStdHandle(STD_INPUT_HANDLE);
    hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);

    /* Initialize the Console Standard Streams */
    ConStreamInit(StdIn , GetStdHandle(STD_INPUT_HANDLE) , UTF8Text, INVALID_CP);
    ConStreamInit(StdOut, GetStdHandle(STD_OUTPUT_HANDLE), UTF8Text, INVALID_CP);
    ConStreamInit(StdErr, GetStdHandle(STD_ERROR_HANDLE) , UTF8Text, INVALID_CP);

    /*
     * Bad usage (too much options) or we use the /? switch.
     * Display help for the MORE command.
     */
    if (argc > 1 && wcscmp(argv[1], L"/?") == 0)
    {
        ConResPuts(StdOut, IDS_USAGE);
        return 0;
    }

    // FIXME: Parse all the remaining parameters.
    // Then the file list can be found at the very end.
    // FIXME2: Use the PARSER api that can be found in EVENTCREATE.

    // NOTE: We might try to duplicate the ConOut for read access... ?
    hKeyboard = CreateFileW(L"CONIN$", GENERIC_READ|GENERIC_WRITE,
                            FILE_SHARE_READ|FILE_SHARE_WRITE, NULL,
                            OPEN_EXISTING, 0, NULL);
    FlushConsoleInputBuffer(hKeyboard);
    ConStreamSetOSHandle(StdIn, hKeyboard);


    FileCacheBuffer = HeapAlloc(GetProcessHeap(), 0, FileCacheBufferSize);
    if (!FileCacheBuffer)
    {
        ConPuts(StdErr, L"Error: no memory\n");
        CloseHandle(hKeyboard);
        return 1;
    }

    /* Special case where we run 'MORE' without any argument: we use STDIN */
    if (argc <= 1)
    {
        /*
         * Assign STDIN handle to hFile so that the page prompt function will
         * know the data comes from STDIN, and will take different actions.
         */
        hFile = hStdIn;

        /* Update the statistics for PagePrompt */
        dwFileSize = 0;
        dwSumReadBytes = dwSumReadChars = 0;

        /* We suppose we read text from the file */

        /* For STDIN we always suppose we are in ANSI mode */
        // SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
        Encoding = ENCODING_ANSI; // ENCODING_UTF8;

        bContinue = ConPutsPaging(&Pager, PagePrompt, TRUE, L"");
        if (!bContinue)
            goto Quit;

        do
        {
            bRet = FileGetString(hFile, Encoding,
                                 FileCacheBuffer, FileCacheBufferSize,
                                 &StringBuffer, &StringBufferLength,
                                 &dwReadBytes, &dwReadChars);
            if (!bRet || dwReadBytes == 0 || dwReadChars == 0)
            {
                /* We failed at reading the file, bail out */
                break;
            }

            /* Update the statistics for PagePrompt */
            dwSumReadBytes += dwReadBytes;
            dwSumReadChars += dwReadChars;

            bContinue = ConWritePaging(&Pager, PagePrompt, FALSE,
                                       StringBuffer, dwReadChars);
            /* If we Ctrl-C/Ctrl-Break, stop everything */
            if (!bContinue)
                goto Quit;
        }
        while (bRet && dwReadBytes > 0);
        goto Quit;
    }

    /* We have files: read them and output them to STDOUT */
    for (i = 1; i < argc; i++)
    {
        GetFullPathNameW(argv[i], ARRAYSIZE(szFullPath), szFullPath, NULL);
        hFile = CreateFileW(szFullPath, 
                            GENERIC_READ,
                            FILE_SHARE_READ,
                            NULL,
                            OPEN_EXISTING,
                            0, // FILE_ATTRIBUTE_NORMAL,
                            NULL);
        if (hFile == INVALID_HANDLE_VALUE)
        {
            ConResPrintf(StdErr, IDS_FILE_ACCESS, szFullPath);
            continue;
        }

        /* We currently do not support files too big */
        dwFileSize = GetFileSize(hFile, NULL);
        if (dwFileSize == INVALID_FILE_SIZE)
        {
            ConPuts(StdErr, L"ERROR: Invalid file size!\n");
            CloseHandle(hFile);
            continue;
        }

        /* We suppose we read text from the file */

        /* Check whether the file is UNICODE and retrieve its encoding */
        SetFilePointer(hFile, 0, NULL, FILE_BEGIN);
        bRet = ReadFile(hFile, FileCacheBuffer, FileCacheBufferSize, &dwReadBytes, NULL);
        IsDataUnicode(FileCacheBuffer, dwReadBytes, &Encoding, &SkipBytes);
        SetFilePointer(hFile, SkipBytes, NULL, FILE_BEGIN);

        /* Update the statistics for PagePrompt */
        dwSumReadBytes = dwSumReadChars = 0;

        bContinue = ConPutsPaging(&Pager, PagePrompt, TRUE, L"");
        if (!bContinue)
        {
            CloseHandle(hFile);
            goto Quit;
        }

        do
        {
            bRet = FileGetString(hFile, Encoding,
                                 FileCacheBuffer, FileCacheBufferSize,
                                 &StringBuffer, &StringBufferLength,
                                 &dwReadBytes, &dwReadChars);
            if (!bRet || dwReadBytes == 0 || dwReadChars == 0)
            {
                /*
                 * We failed at reading the file, bail out and
                 * continue with the other files.
                 */
                break;
            }

            /* Update the statistics for PagePrompt */
            dwSumReadBytes += dwReadBytes;
            dwSumReadChars += dwReadChars;

            if ((Encoding == ENCODING_UTF16LE) || (Encoding == ENCODING_UTF16BE))
            {
                bContinue = ConWritePaging(&Pager, PagePrompt, FALSE,
                                           FileCacheBuffer, dwReadChars);
            }
            else
            {
                bContinue = ConWritePaging(&Pager, PagePrompt, FALSE,
                                           StringBuffer, dwReadChars);
            }
            /* If we Ctrl-C/Ctrl-Break, stop everything */
            if (!bContinue)
            {
                CloseHandle(hFile);
                goto Quit;
            }
        }
        while (bRet && dwReadBytes > 0);

        CloseHandle(hFile);
    }

Quit:
    if (StringBuffer) HeapFree(GetProcessHeap(), 0, StringBuffer);
    HeapFree(GetProcessHeap(), 0, FileCacheBuffer);
    CloseHandle(hKeyboard);
    return 0;
}