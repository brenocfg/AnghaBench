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
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ SIZE_T ;
typedef  scalar_t__ LPBYTE ;
typedef  scalar_t__ HGLOBAL ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CF_OEMTEXT ; 
 int /*<<< orphan*/  CF_UNICODETEXT ; 
 int /*<<< orphan*/  CloseClipboard () ; 
 int /*<<< orphan*/  ConInitStdStreams () ; 
 int /*<<< orphan*/  ConResPuts (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EmptyClipboard () ; 
 scalar_t__ FILE_TYPE_CHAR ; 
 int GMEM_MOVEABLE ; 
 int GMEM_ZEROINIT ; 
 scalar_t__ GetFileType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetStdHandle (int /*<<< orphan*/ ) ; 
 scalar_t__ GlobalAlloc (int,int) ; 
 int /*<<< orphan*/  GlobalFree (scalar_t__) ; 
 scalar_t__ GlobalLock (scalar_t__) ; 
 scalar_t__ GlobalReAlloc (scalar_t__,scalar_t__,int) ; 
 scalar_t__ GlobalSize (scalar_t__) ; 
 int /*<<< orphan*/  GlobalUnlock (scalar_t__) ; 
 int /*<<< orphan*/  IDS_HELP ; 
 int /*<<< orphan*/  IDS_USAGE ; 
 scalar_t__ IsDataUnicode (scalar_t__) ; 
 int /*<<< orphan*/  OpenClipboard (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PrintError (int /*<<< orphan*/ ) ; 
 scalar_t__ ReadFile (int /*<<< orphan*/ ,scalar_t__,int,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STD_INPUT_HANDLE ; 
 int /*<<< orphan*/  SetClipboardData (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  StdOut ; 
 scalar_t__ wcsncmp (int /*<<< orphan*/ *,char*,int) ; 

int wmain(int argc, wchar_t** argv)
{
    HANDLE hInput;
    DWORD dwBytesRead;
    BOOL bStatus;
    HGLOBAL hBuffer;
    HGLOBAL hTemp;
    LPBYTE lpBuffer;
    SIZE_T dwSize = 0;

    /* Initialize the Console Standard Streams */
    hInput = GetStdHandle(STD_INPUT_HANDLE);
    ConInitStdStreams();

    /* Check for usage */
    if (argc > 1 && wcsncmp(argv[1], L"/?", 2) == 0)
    {
        ConResPuts(StdOut, IDS_HELP);
        return 0;
    }

    if (GetFileType(hInput) == FILE_TYPE_CHAR)
    {
        ConResPuts(StdOut, IDS_USAGE);
        return 0;
    }

    /* Initialize a growable buffer for holding clipboard data */
    hBuffer = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, 4096);
    if (!hBuffer)
        goto Failure;

    /*
     * Read data from the input stream by chunks of 4096 bytes
     * and resize the buffer each time when needed.
     */
    do
    {
        lpBuffer = GlobalLock(hBuffer);
        if (!lpBuffer)
            goto Failure;

        bStatus = ReadFile(hInput, lpBuffer + dwSize, 4096, &dwBytesRead, NULL);
        dwSize += dwBytesRead;
        GlobalUnlock(hBuffer);

        hTemp = GlobalReAlloc(hBuffer, GlobalSize(hBuffer) + 4096, GMEM_ZEROINIT);
        if (!hTemp)
            goto Failure;

        hBuffer = hTemp;
    }
    while (bStatus && dwBytesRead > 0);

    /*
     * Resize the buffer to the total size of data read.
     * Note that, if the call fails, we still have the old buffer valid.
     * The old buffer would be larger than the actual size of data it contains,
     * but this is not a problem for us.
     */
    hTemp = GlobalReAlloc(hBuffer, dwSize + sizeof(WCHAR), GMEM_ZEROINIT);
    if (hTemp)
        hBuffer = hTemp;

    /* Attempt to open the clipboard */
    if (!OpenClipboard(NULL))
        goto Failure;

    /* Empty it, copy our data, then close it */

    EmptyClipboard();

    if (IsDataUnicode(hBuffer))
    {
        SetClipboardData(CF_UNICODETEXT, hBuffer);
    }
    else
    {
        // TODO: Convert text from current console page to standard ANSI.
        // Alternatively one can use CF_OEMTEXT as done here.
        SetClipboardData(CF_OEMTEXT, hBuffer);
    }

    CloseClipboard();
    return 0;

Failure:
    if (hBuffer) GlobalFree(hBuffer);
    PrintError(GetLastError());
    return -1;
}