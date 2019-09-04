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
typedef  int /*<<< orphan*/  LPLOGPALETTE ;
typedef  int /*<<< orphan*/  HPALETTE ;
typedef  int /*<<< orphan*/  HGLOBAL ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CF_PALETTE ; 
 int /*<<< orphan*/  ClipboardReadMemoryBlock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreatePalette (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERROR_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GlobalFree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalUnlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetClipboardData (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL ClipboardReadPalette(HANDLE hFile, DWORD dwOffset, DWORD dwLength)
{
    LPLOGPALETTE lpPalette;
    HPALETTE hPalette;
    HGLOBAL hData;

    hData = ClipboardReadMemoryBlock(hFile, dwOffset, dwLength);
    if (!hData)
    {
        return FALSE;
    }

    lpPalette = GlobalLock(hData);
    if (!lpPalette)
    {
        GlobalFree(hData);
        return FALSE;
    }

    hPalette = CreatePalette(lpPalette);
    if (!hPalette)
    {
        GlobalUnlock(hData);
        GlobalFree(hData);
        SetLastError(ERROR_OUTOFMEMORY);
        return FALSE;
    }

    GlobalUnlock(hData);
    GlobalFree(hData);

    if (!SetClipboardData(CF_PALETTE, hPalette))
    {
        DeleteObject(hPalette);
        return FALSE;
    }

    return TRUE;
}