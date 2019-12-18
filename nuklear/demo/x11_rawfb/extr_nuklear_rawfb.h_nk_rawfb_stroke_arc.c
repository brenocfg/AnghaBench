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
 int /*<<< orphan*/  nk_rawfb_ctx_setpixel (struct rawfb_context const*,short,short,struct nk_color const) ; 

__attribute__((used)) static void
nk_rawfb_stroke_arc(const struct rawfb_context *rawfb,
    short x0, short y0, short w, short h, const short s,
    const short line_thickness, const struct nk_color col)
{
    /* Bresenham's ellipses - modified to draw one quarter */
    const int a2 = (w * w) / 4;
    const int b2 = (h * h) / 4;
    const int fa2 = 4 * a2, fb2 = 4 * b2;
    int x, y, sigma;

    if (s != 0 && s != 90 && s != 180 && s != 270) return;
    if (w < 1 || h < 1) return;

    /* Convert upper left to center */
    h = (h + 1) / 2;
    w = (w + 1) / 2;
    x0 += w; y0 += h;

    /* First half */
    for (x = 0, y = h, sigma = 2*b2+a2*(1-2*h); b2*x <= a2*y; x++) {
        if (s == 180)
            nk_rawfb_ctx_setpixel(rawfb, x0 + x, y0 + y, col);
        else if (s == 270)
            nk_rawfb_ctx_setpixel(rawfb, x0 - x, y0 + y, col);
        else if (s == 0)
            nk_rawfb_ctx_setpixel(rawfb, x0 + x, y0 - y, col);
        else if (s == 90)
            nk_rawfb_ctx_setpixel(rawfb, x0 - x, y0 - y, col);
        if (sigma >= 0) {
            sigma += fa2 * (1 - y);
            y--;
        } sigma += b2 * ((4 * x) + 6);
    }

    /* Second half */
    for (x = w, y = 0, sigma = 2*a2+b2*(1-2*w); a2*y <= b2*x; y++) {
        if (s == 180)
            nk_rawfb_ctx_setpixel(rawfb, x0 + x, y0 + y, col);
        else if (s == 270)
            nk_rawfb_ctx_setpixel(rawfb, x0 - x, y0 + y, col);
        else if (s == 0)
            nk_rawfb_ctx_setpixel(rawfb, x0 + x, y0 - y, col);
        else if (s == 90)
            nk_rawfb_ctx_setpixel(rawfb, x0 - x, y0 - y, col);
        if (sigma >= 0) {
            sigma += fb2 * (1 - x);
            x--;
        } sigma += a2 * ((4 * y) + 6);
    }
}