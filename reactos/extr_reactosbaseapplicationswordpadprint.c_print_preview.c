#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; int /*<<< orphan*/  left; } ;
struct TYPE_13__ {int /*<<< orphan*/  cy; int /*<<< orphan*/  cx; } ;
struct TYPE_12__ {int cx; scalar_t__ cy; } ;
struct TYPE_11__ {int cx; int cy; } ;
struct TYPE_15__ {int pages_shown; TYPE_4__ window; int /*<<< orphan*/  zoomratio; TYPE_3__ bmSize; int /*<<< orphan*/  hdc2; TYPE_2__ bmScaledSize; TYPE_1__ spacing; int /*<<< orphan*/  page; int /*<<< orphan*/  hdc; } ;
typedef  TYPE_4__ RECT ;
typedef  int /*<<< orphan*/  PAINTSTRUCT ;
typedef  int /*<<< orphan*/  LRESULT ;
typedef  int /*<<< orphan*/  HWND ;
typedef  int /*<<< orphan*/  HRGN ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  BeginPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CombineRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreatePen (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateRectRgnIndirect (TYPE_4__*) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EndPaint (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FillRect (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FillRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GRAY_BRUSH ; 
 int /*<<< orphan*/  GetClientRect (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int GetScrollPos (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  InflateRect (TYPE_4__*,int,int) ; 
 int PS_INSIDEFRAME ; 
 int PS_SOLID ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RGN_DIFF ; 
 int /*<<< orphan*/  Rectangle (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SB_HORZ ; 
 int /*<<< orphan*/  SB_VERT ; 
 int /*<<< orphan*/  SRCCOPY ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_4__*,int,int,int,scalar_t__) ; 
 int /*<<< orphan*/  SetRectRgn (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StretchBlt (int /*<<< orphan*/ ,int,int,int,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WHITE_BRUSH ; 
 int /*<<< orphan*/  draw_margin_lines (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_last_preview_page (int /*<<< orphan*/ ) ; 
 TYPE_5__ preview ; 

__attribute__((used)) static LRESULT print_preview(HWND hwndPreview)
{
    HPEN hPen, oldPen;
    HDC hdc;
    HRGN back_rgn, excl_rgn;
    RECT window, background;
    PAINTSTRUCT ps;
    int x, y;

    hdc = BeginPaint(hwndPreview, &ps);
    GetClientRect(hwndPreview, &window);
    back_rgn = CreateRectRgnIndirect(&window);

    x = preview.spacing.cx - GetScrollPos(hwndPreview, SB_HORZ);
    y = preview.spacing.cy - GetScrollPos(hwndPreview, SB_VERT);

    /* draw page outlines */
    hPen = CreatePen(PS_SOLID|PS_INSIDEFRAME, 2, RGB(0,0,0));
    oldPen = SelectObject(hdc, hPen);
    SetRect(&background, x - 2, y - 2, x + preview.bmScaledSize.cx + 2,
            y + preview.bmScaledSize.cy + 2);
    Rectangle(hdc, background.left, background.top,
              background.right, background.bottom);
    excl_rgn = CreateRectRgnIndirect(&background);
    CombineRgn(back_rgn, back_rgn, excl_rgn, RGN_DIFF);
    if(preview.pages_shown > 1)
    {
        background.left += preview.bmScaledSize.cx + preview.spacing.cx;
        background.right += preview.bmScaledSize.cx + preview.spacing.cx;
        Rectangle(hdc, background.left, background.top,
                  background.right, background.bottom);
        SetRectRgn(excl_rgn, background.left, background.top,
                   background.right, background.bottom);
        CombineRgn(back_rgn, back_rgn, excl_rgn, RGN_DIFF);
    }
    SelectObject(hdc, oldPen);
    DeleteObject(hPen);
    FillRgn(hdc, back_rgn, GetStockObject(GRAY_BRUSH));
    DeleteObject(excl_rgn);
    DeleteObject(back_rgn);

    StretchBlt(hdc, x, y, preview.bmScaledSize.cx, preview.bmScaledSize.cy,
               preview.hdc, 0, 0, preview.bmSize.cx, preview.bmSize.cy, SRCCOPY);

    draw_margin_lines(hdc, x, y, preview.zoomratio);

    if(preview.pages_shown > 1)
    {
        if (!is_last_preview_page(preview.page)) {
            x += preview.spacing.cx + preview.bmScaledSize.cx;
            StretchBlt(hdc, x, y,
                       preview.bmScaledSize.cx, preview.bmScaledSize.cy,
                       preview.hdc2, 0, 0,
                       preview.bmSize.cx, preview.bmSize.cy, SRCCOPY);

            draw_margin_lines(hdc, x, y, preview.zoomratio);
        } else {
            InflateRect(&background, -2, -2);
            FillRect(hdc, &background, GetStockObject(WHITE_BRUSH));
        }
    }

    preview.window = window;

    EndPaint(hwndPreview, &ps);

    return 0;
}