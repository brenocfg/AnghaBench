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
typedef  char* LPTSTR ;
typedef  char* LPSTR ;
typedef  scalar_t__ INT ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  char CHAR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_CURRENT ; 
 int /*<<< orphan*/  MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,scalar_t__) ; 
 int /*<<< orphan*/  OutputCodePage ; 
 scalar_t__ ReadFile (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetFilePointer (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 char* cmd_alloc (scalar_t__) ; 
 int /*<<< orphan*/  cmd_free (char*) ; 
 char* memchr (char*,char,scalar_t__) ; 

BOOL FileGetString (HANDLE hFile, LPTSTR lpBuffer, INT nBufferLength)
{
    LPSTR lpString;
    DWORD  dwRead;
    INT len = 0;
#ifdef _UNICODE
    lpString = cmd_alloc(nBufferLength);
#else
    lpString = lpBuffer;
#endif

    if (ReadFile(hFile, lpString, nBufferLength - 1, &dwRead, NULL))
    {
        /* break at new line*/
        CHAR *end = memchr(lpString, '\n', dwRead);
        len = dwRead;
        if (end)
        {
            len = (INT)(end - lpString) + 1;
            SetFilePointer(hFile, len - dwRead, NULL, FILE_CURRENT);
        }
    }

    if (!len)
    {
#ifdef _UNICODE
        cmd_free(lpString);
#endif
        return FALSE;
    }

    lpString[len++] = '\0';
#ifdef _UNICODE
    MultiByteToWideChar(OutputCodePage, 0, lpString, -1, lpBuffer, len);
    cmd_free(lpString);
#endif
    return TRUE;
}