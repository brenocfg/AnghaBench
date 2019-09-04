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
struct nk_color {int dummy; } ;
typedef  int /*<<< orphan*/ * HPEN ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/ * CreatePen (int /*<<< orphan*/ ,unsigned short,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DC_PEN ; 
 int /*<<< orphan*/  DeleteObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Ellipse (int /*<<< orphan*/ ,short,short,short,short) ; 
 int /*<<< orphan*/ * GetStockObject (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPAQUE ; 
 int /*<<< orphan*/  PS_SOLID ; 
 int /*<<< orphan*/  SelectObject (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetDCBrushColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 

__attribute__((used)) static void
nk_gdi_stroke_circle(HDC dc, short x, short y, unsigned short w,
    unsigned short h, unsigned short line_thickness, struct nk_color col)
{
    COLORREF color = convert_color(col);
    HPEN pen = NULL;
    if (line_thickness == 1) {
        SetDCPenColor(dc, color);
    } else {
        pen = CreatePen(PS_SOLID, line_thickness, color);
        SelectObject(dc, pen);
    }

    SetDCBrushColor(dc, OPAQUE);
    Ellipse(dc, x, y, x + w, y + h);

    if (pen) {
        SelectObject(dc, GetStockObject(DC_PEN));
        DeleteObject(pen);
    }
}