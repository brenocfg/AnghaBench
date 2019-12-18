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
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int /*<<< orphan*/  Ellipse (int /*<<< orphan*/ ,short,short,short,short) ; 
 int /*<<< orphan*/  SetDCBrushColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 

__attribute__((used)) static void
nk_gdi_fill_circle(HDC dc, short x, short y, unsigned short w,
    unsigned short h, struct nk_color col)
{
    COLORREF color = convert_color(col);
    SetDCBrushColor(dc, color);
    SetDCPenColor(dc, color);
    Ellipse(dc, x, y, x + w, y + h);
}