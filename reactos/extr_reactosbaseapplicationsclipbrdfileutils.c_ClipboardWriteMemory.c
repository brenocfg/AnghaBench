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
typedef  int /*<<< orphan*/ * PDWORD ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  GetClipboardData (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalSize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 scalar_t__ INVALID_SET_FILE_POINTER ; 
 scalar_t__ SetFilePointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WriteFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BOOL ClipboardWriteMemory(HANDLE hFile, DWORD dwFormat, DWORD dwOffset, PDWORD pdwLength)
{
    HGLOBAL hData;
    LPVOID lpData;
    DWORD dwBytesWritten;

    hData = GetClipboardData(dwFormat);
    if (!hData)
        return FALSE;

    lpData = GlobalLock(hData);
    if (!lpData)
        return FALSE;

    *pdwLength = GlobalSize(hData);

    if (SetFilePointer(hFile, dwOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        GlobalUnlock(hData);
        return FALSE;
    }

    if (!WriteFile(hFile, lpData, *pdwLength, &dwBytesWritten, NULL))
    {
        GlobalUnlock(hData);
        return FALSE;
    }

    GlobalUnlock(hData);

    return TRUE;
}