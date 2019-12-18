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
struct rawfb_image {int dummy; } ;
struct nk_rect {float w; float h; float x; float y; } ;
struct nk_color {scalar_t__ b; scalar_t__ g; scalar_t__ r; } ;

/* Variables and functions */
 int /*<<< orphan*/  nk_rawfb_img_blendpixel (struct rawfb_image const*,short,short,struct nk_color) ; 
 struct nk_color nk_rawfb_img_getpixel (struct rawfb_image const*,int,int) ; 

__attribute__((used)) static void
nk_rawfb_stretch_image(const struct rawfb_image *dst,
    const struct rawfb_image *src, const struct nk_rect *dst_rect,
    const struct nk_rect *src_rect, const struct nk_rect *dst_scissors,
    const struct nk_color *fg)
{
    short i, j;
    struct nk_color col;
    float xinc = src_rect->w / dst_rect->w;
    float yinc = src_rect->h / dst_rect->h;
    float xoff = src_rect->x, yoff = src_rect->y;

    /* Simple nearest filtering rescaling */
    /* TODO: use bilinear filter */
    for (j = 0; j < (short)dst_rect->h; j++) {
        for (i = 0; i < (short)dst_rect->w; i++) {
            if (dst_scissors) {
                if (i + (int)(dst_rect->x + 0.5f) < dst_scissors->x || i + (int)(dst_rect->x + 0.5f) >= dst_scissors->w)
                    continue;
                if (j + (int)(dst_rect->y + 0.5f) < dst_scissors->y || j + (int)(dst_rect->y + 0.5f) >= dst_scissors->h)
                    continue;
            }
            col = nk_rawfb_img_getpixel(src, (int)xoff, (int) yoff);
	    if (col.r || col.g || col.b)
	    {
		col.r = fg->r;
		col.g = fg->g;
		col.b = fg->b;
	    }
            nk_rawfb_img_blendpixel(dst, i + (int)(dst_rect->x + 0.5f), j + (int)(dst_rect->y + 0.5f), col);
            xoff += xinc;
        }
        xoff = src_rect->x;
        yoff += yinc;
    }
}