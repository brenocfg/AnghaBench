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
typedef  int /*<<< orphan*/  HMETAFILE ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CF_METAFILEPICT ; 
 int /*<<< orphan*/  ClipboardReadMemoryBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteMetaFile (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetClipboardData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetMetaFileBitsEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL ClipboardReadMetafile(HANDLE hFile, DWORD dwOffset, DWORD dwLength)
{
    HMETAFILE hMf;
    HGLOBAL hData;
    LPVOID lpData;

    hData = ClipboardReadMemoryBlock(hFile, dwOffset, dwLength);
    if (!hData)
    {
        return FALSE;
    }

    lpData = GlobalLock(hData);
    if (!lpData)
    {
        GlobalFree(hData);
        return FALSE;
    }

    hMf = SetMetaFileBitsEx(dwLength, lpData);

    GlobalUnlock(hData);
    GlobalFree(hData);

    if (!hMf)
    {
        SetLastError(ERROR_OUTOFMEMORY);
        return FALSE;
    }

    if (!SetClipboardData(CF_METAFILEPICT, hMf))
    {
        DeleteMetaFile(hMf);
        return FALSE;
    }

    return TRUE;
}