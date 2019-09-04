#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_6__ {int /*<<< orphan*/ * crColor; } ;
struct TYPE_8__ {scalar_t__* hbmpColor; TYPE_1__ SchemeAdv; } ;
struct TYPE_7__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_2__ RECT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  HBRUSH ;
typedef  TYPE_3__ GLOBALS ;

/* Variables and functions */
 int /*<<< orphan*/  BM_SETIMAGE ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EnableWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int) ; 
 scalar_t__ IMAGE_BITMAP ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static VOID
UpdateButtonColor(HWND hwndDlg, GLOBALS* g, INT ID, INT nButton, INT nColor)
{
    HDC hdcColorButton, hdcCompat;
    RECT rect;
    HBRUSH hbrush;
    HWND hwndColorButton;
    HGDIOBJ hgdiTmp;

    if (nColor != -1)
    {
        /* Create a DC to draw on */
        hwndColorButton = GetDlgItem(hwndDlg, ID);
        hdcColorButton = GetDC(hwndColorButton);
        hdcCompat = CreateCompatibleDC(hdcColorButton);
        ReleaseDC(hwndColorButton, hdcColorButton);

        /* Select the button image to it */
        hgdiTmp = SelectObject(hdcCompat, g->hbmpColor[nButton]);

        /* Create a brush and draw the rectangle */
        rect.left = 2;
        rect.top = 2;
        rect.right = 22;
        rect.bottom = 13;
        hbrush = CreateSolidBrush(g->SchemeAdv.crColor[nColor]);
        FillRect(hdcCompat, &rect, hbrush);
        DeleteObject(hbrush);

        /* hdcCompat is not needed anymore */
        SelectObject(hdcCompat,hgdiTmp);
        DeleteDC(hdcCompat);

        SendDlgItemMessage(hwndDlg, ID, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g->hbmpColor[nButton]);
        EnableWindow(GetDlgItem(hwndDlg, ID), TRUE);
    }
    else
    {
        SendDlgItemMessage(hwndDlg, ID, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)NULL);
        EnableWindow(GetDlgItem(hwndDlg, ID), FALSE);
    }
}