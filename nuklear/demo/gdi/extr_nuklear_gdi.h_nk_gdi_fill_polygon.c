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
struct nk_vec2i {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct nk_color {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ POINT ;
typedef  int /*<<< orphan*/  HDC ;
typedef  int /*<<< orphan*/  COLORREF ;

/* Variables and functions */
 int MAX_POINTS ; 
 int /*<<< orphan*/  Polygon (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  SetDCBrushColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetDCPenColor (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert_color (struct nk_color) ; 

__attribute__((used)) static void
nk_gdi_fill_polygon(HDC dc, const struct nk_vec2i *pnts, int count, struct nk_color col)
{
    int i = 0;
    #define MAX_POINTS 64
    POINT points[MAX_POINTS];
    COLORREF color = convert_color(col);
    SetDCBrushColor(dc, color);
    SetDCPenColor(dc, color);
    for (i = 0; i < count && i < MAX_POINTS; ++i) {
        points[i].x = pnts[i].x;
        points[i].y = pnts[i].y;
    }
    Polygon(dc, points, i);
    #undef MAX_POINTS
}