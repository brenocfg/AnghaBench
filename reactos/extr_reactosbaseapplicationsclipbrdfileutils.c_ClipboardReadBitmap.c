#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* bmBits; } ;
typedef  TYPE_1__* LPBITMAP ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HBITMAP ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;
typedef  int /*<<< orphan*/  BITMAP ;

/* Variables and functions */
 int /*<<< orphan*/  CF_BITMAP ; 
 int /*<<< orphan*/  ClipboardReadMemoryBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateBitmapIndirect (TYPE_1__*) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 TYPE_1__* GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetClipboardData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL ClipboardReadBitmap(HANDLE hFile, DWORD dwOffset, DWORD dwLength)
{
    HGLOBAL hData;
    HBITMAP hBitmap;
    LPBITMAP lpBitmap;

    hData = ClipboardReadMemoryBlock(hFile, dwOffset, dwLength);
    if (!hData)
    {
        return FALSE;
    }

    lpBitmap = GlobalLock(hData);
    if (!lpBitmap)
    {
        GlobalFree(hData);
        return FALSE;
    }

    lpBitmap->bmBits = lpBitmap + sizeof(BITMAP) + 1;

    hBitmap = CreateBitmapIndirect(lpBitmap);

    GlobalUnlock(hData);
    GlobalFree(hData);

    if (!hBitmap)
    {
        SetLastError(ERROR_OUTOFMEMORY);
        return FALSE;
    }

    if (!SetClipboardData(CF_BITMAP, hBitmap))
    {
        DeleteObject(hBitmap);
        return FALSE;
    }

    return TRUE;
}