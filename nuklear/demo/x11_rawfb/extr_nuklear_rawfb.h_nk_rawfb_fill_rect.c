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
struct nk_vec2i {short x; short y; } ;
struct nk_color {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nk_rawfb_fill_arc (struct rawfb_context const*,short const,short const,unsigned int,unsigned int,int,struct nk_color const) ; 
 int /*<<< orphan*/  nk_rawfb_fill_polygon (struct rawfb_context const*,struct nk_vec2i*,int,struct nk_color const) ; 
 int /*<<< orphan*/  nk_rawfb_stroke_line (struct rawfb_context const*,short const,short const,short const,short const,int,struct nk_color const) ; 

__attribute__((used)) static void
nk_rawfb_fill_rect(const struct rawfb_context *rawfb,
    const short x, const short y, const short w, const short h,
    const short r, const struct nk_color col)
{
    int i;
    if (r == 0) {
        for (i = 0; i < h; i++)
            nk_rawfb_stroke_line(rawfb, x, y + i, x + w, y + i, 1, col);
    } else {
        const short xc = x + r;
        const short yc = y + r;
        const short wc = (short)(w - 2 * r);
        const short hc = (short)(h - 2 * r);

        struct nk_vec2i pnts[12];
        pnts[0].x = x;
        pnts[0].y = yc;
        pnts[1].x = xc;
        pnts[1].y = yc;
        pnts[2].x = xc;
        pnts[2].y = y;

        pnts[3].x = xc + wc;
        pnts[3].y = y;
        pnts[4].x = xc + wc;
        pnts[4].y = yc;
        pnts[5].x = x + w;
        pnts[5].y = yc;

        pnts[6].x = x + w;
        pnts[6].y = yc + hc;
        pnts[7].x = xc + wc;
        pnts[7].y = yc + hc;
        pnts[8].x = xc + wc;
        pnts[8].y = y + h;

        pnts[9].x = xc;
        pnts[9].y = y + h;
        pnts[10].x = xc;
        pnts[10].y = yc + hc;
        pnts[11].x = x;
        pnts[11].y = yc + hc;

        nk_rawfb_fill_polygon(rawfb, pnts, 12, col);

        nk_rawfb_fill_arc(rawfb, xc + wc - r, y,
                (unsigned)r*2, (unsigned)r*2, 0 , col);
        nk_rawfb_fill_arc(rawfb, x, y,
                (unsigned)r*2, (unsigned)r*2, 90 , col);
        nk_rawfb_fill_arc(rawfb, x, yc + hc - r,
                (unsigned)r*2, (unsigned)r*2, 270 , col);
        nk_rawfb_fill_arc(rawfb, xc + wc - r, yc + hc - r,
                (unsigned)r*2, (unsigned)r*2, 180 , col);
    }
}