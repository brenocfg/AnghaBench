#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
struct TYPE_2__ {int /*<<< orphan*/  hMainWnd; int /*<<< orphan*/  hInstance; } ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int /*<<< orphan*/ * HWND ;
typedef  int /*<<< orphan*/ * HICON ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETIMAGE ; 
 int /*<<< orphan*/  DestroyIcon (int /*<<< orphan*/ *) ; 
 int FALSE ; 
 int /*<<< orphan*/ * GetDlgItem (int /*<<< orphan*/ ,int) ; 
 TYPE_1__ Globals ; 
 scalar_t__ IMAGE_ICON ; 
 int /*<<< orphan*/  LR_DEFAULTCOLOR ; 
 scalar_t__ LoadImageW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAKEINTRESOURCEW (int) ; 
 int /*<<< orphan*/  SendMessageW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TRUE ; 

int OSK_SetImage(int IdDlgItem, int IdResource)
{
    HICON hIcon;
    HWND hWndItem;

    hIcon = (HICON)LoadImageW(Globals.hInstance, MAKEINTRESOURCEW(IdResource),
                              IMAGE_ICON, 16, 16, LR_DEFAULTCOLOR);
    if (hIcon == NULL)
        return FALSE;

    hWndItem = GetDlgItem(Globals.hMainWnd, IdDlgItem);
    if (hWndItem == NULL)
    {
        DestroyIcon(hIcon);
        return FALSE;
    }

    SendMessageW(hWndItem, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)hIcon);

    /* The system automatically deletes these resources when the process that created them terminates (MSDN) */

    return TRUE;
}