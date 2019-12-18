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
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/ * HGLOBAL ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FILE_BEGIN ; 
 int /*<<< orphan*/  GHND ; 
 int /*<<< orphan*/ * GlobalAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ *) ; 
 scalar_t__ INVALID_SET_FILE_POINTER ; 
 int /*<<< orphan*/  ReadFile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ SetFilePointer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HGLOBAL ClipboardReadMemoryBlock(HANDLE hFile, DWORD dwOffset, DWORD dwLength)
{
    HGLOBAL hData;
    LPVOID lpData;
    DWORD dwBytesRead;

    hData = GlobalAlloc(GHND, dwLength);
    if (!hData)
        return NULL;

    lpData = GlobalLock(hData);
    if (!lpData)
    {
        GlobalFree(hData);
        return NULL;
    }

    if (SetFilePointer(hFile, dwOffset, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
    {
        GlobalUnlock(hData);
        GlobalFree(hData);
        return NULL;
    }

    if (!ReadFile(hFile, lpData, dwLength, &dwBytesRead, NULL))
    {
        GlobalUnlock(hData);
        GlobalFree(hData);
        return NULL;
    }

    GlobalUnlock(hData);

    return hData;
}