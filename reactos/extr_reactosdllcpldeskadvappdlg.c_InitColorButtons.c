#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WPARAM ;
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_11__ {int /*<<< orphan*/ * crColor; } ;
struct TYPE_10__ {scalar_t__* hbmpColor; TYPE_4__ SchemeAdv; } ;
struct TYPE_9__ {int member_0; int member_1; } ;
struct TYPE_8__ {int left; int top; int right; int bottom; } ;
typedef  TYPE_1__ RECT ;
typedef  TYPE_2__ POINT ;
typedef  int /*<<< orphan*/  LPARAM ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  scalar_t__ HPEN ;
typedef  scalar_t__ HGDIOBJ ;
typedef  int /*<<< orphan*/  HDC ;
typedef  scalar_t__ HBRUSH ;
typedef  TYPE_3__ GLOBALS ;
typedef  TYPE_4__ COLOR_SCHEME ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK_PEN ; 
 int /*<<< orphan*/  BM_SETIMAGE ; 
 size_t COLOR_BTNFACE ; 
 size_t COLOR_BTNHIGHLIGHT ; 
 size_t COLOR_BTNSHADOW ; 
 size_t COLOR_BTNTEXT ; 
 scalar_t__ CreateCompatibleBitmap (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  CreateCompatibleDC (int /*<<< orphan*/ ) ; 
 scalar_t__ CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ CreateSolidBrush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (scalar_t__) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  GetDC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDlgItem (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDC_ADVAPPEARANCE_COLOR1_B ; 
 int /*<<< orphan*/  IDC_ADVAPPEARANCE_COLOR2_B ; 
 int /*<<< orphan*/  IDC_ADVAPPEARANCE_FONTCOLOR_B ; 
 scalar_t__ IMAGE_BITMAP ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  Polygon (int /*<<< orphan*/ ,TYPE_2__ const*,int) ; 
 int /*<<< orphan*/  ReleaseDC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SelectObject (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  SendDlgItemMessage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetPolyFillMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WINDING ; 

__attribute__((used)) static VOID
InitColorButtons(HWND hwndDlg, GLOBALS* g)
{
    INT i;
    HDC hdcColorButton, hdcCompat;
    RECT rect;
    HBRUSH hbrush;
    HPEN hPen;
    HWND hwndColorButton;
    HGDIOBJ hgdiTemp;
    COLOR_SCHEME *scheme = &g->SchemeAdv;

    const POINT Points[3] = {{29,6},{33,6},{31,8}};

    hwndColorButton = GetDlgItem(hwndDlg, IDC_ADVAPPEARANCE_COLOR1_B);
    hdcColorButton = GetDC(hwndColorButton);
    for (i = 0; i <= 2; i++)
    {
        /* Create a DC to draw on */
        hdcCompat = CreateCompatibleDC(hdcColorButton);

        /* Create the button image */
        g->hbmpColor[i] = CreateCompatibleBitmap(hdcColorButton, 36, 15);

        /* Select the button image to the DC */
        hgdiTemp = SelectObject(hdcCompat, g->hbmpColor[i]);

        /* Draw the buttons background color */
        rect.left = 0;
        rect.top = 0;
        rect.right = 36;
        rect.bottom = 15;
        hbrush = CreateSolidBrush(scheme->crColor[COLOR_BTNFACE]);
        FillRect(hdcCompat, &rect, hbrush);
        DeleteObject(hbrush);

        /* Draw the rectangle */
        rect.left = 1;
        rect.top = 1;
        rect.right = 23;
        rect.bottom = 14;
        hbrush = CreateSolidBrush(scheme->crColor[COLOR_BTNTEXT]);
        FillRect(hdcCompat, &rect, hbrush);
        DeleteObject(hbrush);

        /* Draw left side of line */
        hPen = CreatePen(PS_SOLID, 1, scheme->crColor[COLOR_BTNSHADOW]);
        SelectObject(hdcCompat, hPen);
        MoveToEx(hdcCompat, 26, 1, NULL);
        LineTo(hdcCompat, 26, 14);
        SelectObject(hdcCompat, GetStockObject(BLACK_PEN));
        DeleteObject(hPen);

        /* Draw right side of line */
        hPen = CreatePen(PS_SOLID, 1, scheme->crColor[COLOR_BTNHIGHLIGHT]);
        SelectObject(hdcCompat,hPen);
        MoveToEx(hdcCompat, 27, 1, NULL);
        LineTo(hdcCompat, 27, 14);
        SelectObject(hdcCompat, GetStockObject(BLACK_PEN));
        DeleteObject(hPen);

        /* Draw triangle */
        hPen = CreatePen(PS_SOLID, 1, scheme->crColor[COLOR_BTNTEXT]);
        hbrush = CreateSolidBrush(scheme->crColor[COLOR_BTNTEXT]);
        SelectObject(hdcCompat, hPen);
        SelectObject(hdcCompat, hbrush);
        SetPolyFillMode(hdcCompat, WINDING);

        /* FIXME: HACK, see Points definition */
        Polygon(hdcCompat, Points, 3);

        /* Cleanup */
        SelectObject(hdcCompat,hgdiTemp);
        DeleteDC(hdcCompat);
        DeleteObject(hPen);
        DeleteObject(hbrush);
    }

    ReleaseDC(hwndColorButton, hdcColorButton);

    /* Set the images of the buttons */
    SendDlgItemMessage(hwndDlg, IDC_ADVAPPEARANCE_COLOR1_B, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g->hbmpColor[0]);
    SendDlgItemMessage(hwndDlg, IDC_ADVAPPEARANCE_COLOR2_B, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g->hbmpColor[1]);
    SendDlgItemMessage(hwndDlg, IDC_ADVAPPEARANCE_FONTCOLOR_B, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)g->hbmpColor[2]);
}