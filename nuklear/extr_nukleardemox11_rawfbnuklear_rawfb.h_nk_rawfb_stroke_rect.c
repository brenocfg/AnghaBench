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
struct nk_color {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  nk_rawfb_stroke_arc (struct rawfb_context const*,short const,short const,unsigned int,unsigned int,int,short const,struct nk_color const) ; 
 int /*<<< orphan*/  nk_rawfb_stroke_line (struct rawfb_context const*,short const,short const,short const,short const,short const,struct nk_color const) ; 

__attribute__((used)) static void
nk_rawfb_stroke_rect(const struct rawfb_context *rawfb,
    const short x, const short y, const short w, const short h,
    const short r, const short line_thickness, const struct nk_color col)
{
    if (r == 0) {
        nk_rawfb_stroke_line(rawfb, x, y, x + w, y, line_thickness, col);
        nk_rawfb_stroke_line(rawfb, x, y + h, x + w, y + h, line_thickness, col);
        nk_rawfb_stroke_line(rawfb, x, y, x, y + h, line_thickness, col);
        nk_rawfb_stroke_line(rawfb, x + w, y, x + w, y + h, line_thickness, col);
    } else {
        const short xc = x + r;
        const short yc = y + r;
        const short wc = (short)(w - 2 * r);
        const short hc = (short)(h - 2 * r);

        nk_rawfb_stroke_line(rawfb, xc, y, xc + wc, y, line_thickness, col);
        nk_rawfb_stroke_line(rawfb, x + w, yc, x + w, yc + hc, line_thickness, col);
        nk_rawfb_stroke_line(rawfb, xc, y + h, xc + wc, y + h, line_thickness, col);
        nk_rawfb_stroke_line(rawfb, x, yc, x, yc + hc, line_thickness, col);

        nk_rawfb_stroke_arc(rawfb, xc + wc - r, y,
                (unsigned)r*2, (unsigned)r*2, 0 , line_thickness, col);
        nk_rawfb_stroke_arc(rawfb, x, y,
                (unsigned)r*2, (unsigned)r*2, 90 , line_thickness, col);
        nk_rawfb_stroke_arc(rawfb, x, yc + hc - r,
                (unsigned)r*2, (unsigned)r*2, 270 , line_thickness, col);
        nk_rawfb_stroke_arc(rawfb, xc + wc - r, yc + hc - r,
                (unsigned)r*2, (unsigned)r*2, 180 , line_thickness, col);
    }
}