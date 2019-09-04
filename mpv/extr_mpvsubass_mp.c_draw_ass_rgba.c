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
typedef  int uint32_t ;

/* Variables and functions */

__attribute__((used)) static void draw_ass_rgba(unsigned char *src, int src_w, int src_h,
                          int src_stride, unsigned char *dst, size_t dst_stride,
                          int dst_x, int dst_y, uint32_t color)
{
    const unsigned int r = (color >> 24) & 0xff;
    const unsigned int g = (color >> 16) & 0xff;
    const unsigned int b = (color >>  8) & 0xff;
    const unsigned int a = 0xff - (color & 0xff);

    dst += dst_y * dst_stride + dst_x * 4;

    for (int y = 0; y < src_h; y++, dst += dst_stride, src += src_stride) {
        uint32_t *dstrow = (uint32_t *) dst;
        for (int x = 0; x < src_w; x++) {
            const unsigned int v = src[x];
            int rr = (r * a * v);
            int gg = (g * a * v);
            int bb = (b * a * v);
            int aa =      a * v;
            uint32_t dstpix = dstrow[x];
            unsigned int dstb =  dstpix        & 0xFF;
            unsigned int dstg = (dstpix >>  8) & 0xFF;
            unsigned int dstr = (dstpix >> 16) & 0xFF;
            unsigned int dsta = (dstpix >> 24) & 0xFF;
            dstb = (bb       + dstb * (255 * 255 - aa)) / (255 * 255);
            dstg = (gg       + dstg * (255 * 255 - aa)) / (255 * 255);
            dstr = (rr       + dstr * (255 * 255 - aa)) / (255 * 255);
            dsta = (aa * 255 + dsta * (255 * 255 - aa)) / (255 * 255);
            dstrow[x] = dstb | (dstg << 8) | (dstr << 16) | (dsta << 24);
        }
    }
}