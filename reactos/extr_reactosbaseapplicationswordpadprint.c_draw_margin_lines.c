#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int left; int top; int right; int bottom; } ;
struct TYPE_8__ {int cx; int cy; } ;
struct TYPE_10__ {int left; int top; int right; int bottom; } ;
struct TYPE_11__ {TYPE_1__ bmScaledSize; TYPE_3__ rcPage; } ;
struct TYPE_9__ {void* cx; void* cy; } ;
typedef  TYPE_2__ SIZE ;
typedef  TYPE_3__ RECT ;
typedef  int /*<<< orphan*/  HPEN ;
typedef  int /*<<< orphan*/  HDC ;

/* Variables and functions */
 int /*<<< orphan*/  CreatePen (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ ) ; 
 void* GetDeviceCaps (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LOGPIXELSX ; 
 int /*<<< orphan*/  LOGPIXELSY ; 
 int /*<<< orphan*/  LineTo (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  MoveToEx (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OffsetRect (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  PS_DOT ; 
 int /*<<< orphan*/  RGB (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetRect (TYPE_3__*,int,int,int,int) ; 
 TYPE_5__ margins ; 
 TYPE_4__ preview ; 
 scalar_t__ twips_to_pixels (int,void*) ; 

__attribute__((used)) static void draw_margin_lines(HDC hdc, int x, int y, float ratio)
{
    HPEN hPen, oldPen;
    SIZE dpi;
    RECT page_margin = preview.rcPage;

    dpi.cx = GetDeviceCaps(hdc, LOGPIXELSX);
    dpi.cy = GetDeviceCaps(hdc, LOGPIXELSY);

    SetRect(&page_margin, preview.rcPage.left + margins.left, preview.rcPage.top + margins.top,
            preview.rcPage.right - margins.right, preview.rcPage.bottom - margins.bottom);

    page_margin.left = (int)((float)twips_to_pixels(page_margin.left, dpi.cx) * ratio);
    page_margin.top = (int)((float)twips_to_pixels(page_margin.top, dpi.cy) * ratio);
    page_margin.bottom = (int)((float)twips_to_pixels(page_margin.bottom, dpi.cy) * ratio);
    page_margin.right = (int)((float)twips_to_pixels(page_margin.right, dpi.cx) * ratio);

    OffsetRect(&page_margin, x, y);

    hPen = CreatePen(PS_DOT, 1, RGB(0,0,0));
    oldPen = SelectObject(hdc, hPen);

    MoveToEx(hdc, x, page_margin.top, NULL);
    LineTo(hdc, x + preview.bmScaledSize.cx, page_margin.top);
    MoveToEx(hdc, x, page_margin.bottom, NULL);
    LineTo(hdc, x + preview.bmScaledSize.cx, page_margin.bottom);

    MoveToEx(hdc, page_margin.left, y, NULL);
    LineTo(hdc, page_margin.left, y + preview.bmScaledSize.cy);
    MoveToEx(hdc, page_margin.right, y, NULL);
    LineTo(hdc, page_margin.right, y + preview.bmScaledSize.cy);

    SelectObject(hdc, oldPen);
    DeleteObject(hPen);
}