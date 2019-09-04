#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ dwHighDateTime; scalar_t__ dwLowDateTime; } ;
typedef  int /*<<< orphan*/  TCHAR ;
typedef  int /*<<< orphan*/ * LPBYTE ;
typedef  int INT ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_1__ FILETIME ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  BREAK_INPUT ; 
 int /*<<< orphan*/  BUFF_SIZE ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 scalar_t__ CheckCtrlBreak (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  ConOutResPaging (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConOutResPrintf (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ConOutResPuts (int /*<<< orphan*/ ) ; 
 scalar_t__ CreateFile (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FILE_SHARE_READ ; 
 int /*<<< orphan*/  FilePromptYNA (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int GetFileAttributes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetFileTime (scalar_t__,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  GetPathCase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 scalar_t__ IsExistingFile (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  MEM_COMMIT ; 
 int /*<<< orphan*/  MEM_RELEASE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  PAGE_READWRITE ; 
 int REPLACE_ADD ; 
 int REPLACE_CONFIRM ; 
 int REPLACE_UPDATE ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STRING_COPY_ERROR1 ; 
 int /*<<< orphan*/  STRING_COPY_ERROR3 ; 
 int /*<<< orphan*/  STRING_ERROR_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  STRING_REPLACE_ERROR7 ; 
 int /*<<< orphan*/  STRING_REPLACE_HELP10 ; 
 int /*<<< orphan*/  STRING_REPLACE_HELP11 ; 
 int /*<<< orphan*/  STRING_REPLACE_HELP5 ; 
 int /*<<< orphan*/  STRING_REPLACE_HELP9 ; 
 int /*<<< orphan*/  SetFileAttributes (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetFileTime (scalar_t__,TYPE_1__*,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * VirtualAlloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VirtualFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,int /*<<< orphan*/ *,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _tcscmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _totupper (int /*<<< orphan*/ ) ; 
 int nErrorLevel ; 

INT replace(TCHAR source[MAX_PATH], TCHAR dest[MAX_PATH], DWORD dwFlags, BOOL *doMore)
{
    TCHAR d[MAX_PATH];
    TCHAR s[MAX_PATH];
    HANDLE hFileSrc, hFileDest;
    DWORD  dwAttrib, dwRead, dwWritten;
    LPBYTE buffer;
    BOOL   bEof = FALSE;
    FILETIME srcCreationTime, destCreationTime, srcLastAccessTime, destLastAccessTime;
    FILETIME srcLastWriteTime, destLastWriteTime;
    GetPathCase(source, s);
    GetPathCase(dest, d);
    s[0] = _totupper(s[0]);
    d[0] = _totupper(d[0]);
    // ConOutPrintf(_T("old-src:  %s\n"), s);
    // ConOutPrintf(_T("old-dest: %s\n"), d);
    // ConOutPrintf(_T("src:  %s\n"), source);
    // ConOutPrintf(_T("dest: %s\n"), dest);

    /* Open up the sourcefile */
    hFileSrc = CreateFile (source, GENERIC_READ, FILE_SHARE_READ,NULL, OPEN_EXISTING, 0, NULL);
    if (hFileSrc == INVALID_HANDLE_VALUE)
    {
        ConOutResPrintf(STRING_COPY_ERROR1, source);
        return 0;
    }

    /*
     * Get the time from source file to be used in the comparison
     * with dest time if update switch is set.
     */
    GetFileTime (hFileSrc, &srcCreationTime, &srcLastAccessTime, &srcLastWriteTime);

    /*
     * Retrieve the source attributes so that they later on
     * can be inserted in to the destination.
     */
    dwAttrib = GetFileAttributes (source);

    if (IsExistingFile (dest))
    {
        /*
         * Resets the attributes to avoid problems with read only files,
         * checks for read only has been made earlier.
         */
        SetFileAttributes(dest,FILE_ATTRIBUTE_NORMAL);
        /*
         * Is the update flas set? The time has to be controled so that
         * only older files are replaced.
         */
        if (dwFlags & REPLACE_UPDATE)
        {
            /* Read destination time */
            hFileDest = CreateFile(dest, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                0, NULL);

            if (hFileDest == INVALID_HANDLE_VALUE)
            {
                ConOutResPrintf(STRING_COPY_ERROR1, dest);
                CloseHandle (hFileSrc);
                return 0;
            }

            /* Compare time */
            GetFileTime (hFileDest, &destCreationTime, &destLastAccessTime, &destLastWriteTime);
            if (!((srcLastWriteTime.dwHighDateTime > destLastWriteTime.dwHighDateTime) ||
                    (srcLastWriteTime.dwHighDateTime == destLastWriteTime.dwHighDateTime &&
                     srcLastWriteTime.dwLowDateTime > destLastWriteTime.dwLowDateTime)))
            {
                CloseHandle (hFileSrc);
                CloseHandle (hFileDest);
                return 0;
            }
            CloseHandle (hFileDest);
        }
        /* Delete the old file */
        DeleteFile (dest);
    }

    /* Check confirm flag, and take appropriate action */
    if (dwFlags & REPLACE_CONFIRM)
    {
        /* Output depending on add flag */
        if (dwFlags & REPLACE_ADD)
            ConOutResPrintf(STRING_REPLACE_HELP9, dest);
        else
            ConOutResPrintf(STRING_REPLACE_HELP10, dest);
        if ( !FilePromptYNA (0))
        {
            CloseHandle (hFileSrc);
            return 0;
        }
    }

    /* Output depending on add flag */
    if (dwFlags & REPLACE_ADD)
        ConOutResPrintf(STRING_REPLACE_HELP11, dest);
    else
        ConOutResPrintf(STRING_REPLACE_HELP5, dest);

    /* Make sure source and destination is not the same */
    if (!_tcscmp(s, d))
    {
        ConOutResPaging(TRUE, STRING_REPLACE_ERROR7);
        CloseHandle (hFileSrc);
        *doMore = FALSE;
        return 0;
    }

    /* Open destination file to write to */
    hFileDest = CreateFile (dest, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    if (hFileDest == INVALID_HANDLE_VALUE)
    {
        CloseHandle (hFileSrc);
        ConOutResPaging(TRUE, STRING_REPLACE_ERROR7);
        *doMore = FALSE;
        return 0;
    }

    /* Get buffer for the copy process */
    buffer = VirtualAlloc(NULL, BUFF_SIZE, MEM_COMMIT, PAGE_READWRITE);
    if (buffer == NULL)
    {
        CloseHandle (hFileDest);
        CloseHandle (hFileSrc);
        ConOutResPaging(TRUE, STRING_ERROR_OUT_OF_MEMORY);
        return 0;
    }

    /* Put attribute and time to the new destination file */
    SetFileAttributes (dest, dwAttrib);
    SetFileTime (hFileDest, &srcCreationTime, &srcLastAccessTime, &srcLastWriteTime);
    do
    {
        /* Read data from source */
        ReadFile (hFileSrc, buffer, BUFF_SIZE, &dwRead, NULL);

        /* Done? */
        if (dwRead == 0)
            break;

        /* Write to destination file */
        WriteFile (hFileDest, buffer, dwRead, &dwWritten, NULL);

        /* Done! or ctrl break! */
        if (dwWritten != dwRead || CheckCtrlBreak(BREAK_INPUT))
        {
            ConOutResPuts(STRING_COPY_ERROR3);
            VirtualFree (buffer, 0, MEM_RELEASE);
            CloseHandle (hFileDest);
            CloseHandle (hFileSrc);
            nErrorLevel = 1;
            return 0;
        }
    }
    while (!bEof);

    /* Return memory and close files */
    VirtualFree (buffer, 0, MEM_RELEASE);
    CloseHandle (hFileDest);
    CloseHandle (hFileSrc);

    /* Return one file replaced */
    return 1;
}