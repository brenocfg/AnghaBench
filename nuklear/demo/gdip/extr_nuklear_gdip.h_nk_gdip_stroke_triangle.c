#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct nk_color {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  pen; int /*<<< orphan*/  memory; } ;
struct TYPE_4__ {short member_0; short member_1; } ;
typedef  int /*<<< orphan*/  REAL ;
typedef  TYPE_1__ POINT ;

/* Variables and functions */
 int /*<<< orphan*/  GdipDrawPolygonI (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  GdipSetPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GdipSetPenWidth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 
 TYPE_2__ gdip ; 

__attribute__((used)) static void
nk_gdip_stroke_triangle(short x0, short y0, short x1,
    short y1, short x2, short y2, unsigned short line_thickness, struct nk_color col)
{
    POINT points[] = {
        { x0, y0 },
        { x1, y1 },
        { x2, y2 },
        { x0, y0 },
    };
    GdipSetPenWidth(gdip.pen, (REAL)line_thickness);
    GdipSetPenColor(gdip.pen, convert_color(col));
    GdipDrawPolygonI(gdip.memory, gdip.pen, points, 4);
}