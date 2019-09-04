#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct nk_color {int dummy; } ;
struct TYPE_3__ {short member_0; short member_1; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/ * CreatePen (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_PEN ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  Polyline (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetDCPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 

__attribute__((used)) static void
nk_gdi_stroke_triangle(HDC dc, short x0, short y0, short x1,
    short y1, short x2, short y2, unsigned short line_thickness, struct nk_color col)
{
    COLORREF color = convert_color(col);
    POINT points[] = {
        { x0, y0 },
        { x1, y1 },
        { x2, y2 },
        { x0, y0 },
    };

    HPEN pen = NULL;
    if (line_thickness == 1) {
        SetDCPenColor(dc, color);
    } else {
        pen = CreatePen(PS_SOLID, line_thickness, color);
        SelectObject(dc, pen);
    }

    Polyline(dc, points, 4);

    if (pen) {
        SelectObject(dc, GetStockObject(DC_PEN));
        DeleteObject(pen);
    }
}