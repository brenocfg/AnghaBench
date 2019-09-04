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
struct nk_vec2i {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct nk_color {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  pen; int /*<<< orphan*/  memory; } ;
typedef  int /*<<< orphan*/  REAL ;

/* Variables and functions */
 int /*<<< orphan*/  GdipDrawLineI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetPenWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 
 TYPE_1__ gdip ; 

__attribute__((used)) static void
nk_gdip_stroke_polyline(const struct nk_vec2i *pnts,
    int count, unsigned short line_thickness, struct nk_color col)
{
    GdipSetPenWidth(gdip.pen, (REAL)line_thickness);
    GdipSetPenColor(gdip.pen, convert_color(col));
    if (count > 0) {
        int i;
        for (i = 1; i < count; ++i)
            GdipDrawLineI(gdip.memory, gdip.pen, pnts[i-1].x, pnts[i-1].y, pnts[i].x, pnts[i].y);
    }
}