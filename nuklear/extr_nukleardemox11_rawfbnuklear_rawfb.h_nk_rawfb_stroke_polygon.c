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
struct rawfb_context {int dummy; } ;
struct nk_vec2i {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct nk_color {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nk_rawfb_stroke_line (struct rawfb_context const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned short const,struct nk_color const) ; 

__attribute__((used)) static void
nk_rawfb_stroke_polygon(const struct rawfb_context *rawfb,
    const struct nk_vec2i *pnts, const int count,
    const unsigned short line_thickness, const struct nk_color col)
{
    int i;
    for (i = 1; i < count; ++i)
        nk_rawfb_stroke_line(rawfb, pnts[i-1].x, pnts[i-1].y, pnts[i].x,
                pnts[i].y, line_thickness, col);
    nk_rawfb_stroke_line(rawfb, pnts[count-1].x, pnts[count-1].y,
            pnts[0].x, pnts[0].y, line_thickness, col);
}