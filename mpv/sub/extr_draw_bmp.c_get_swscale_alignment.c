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
struct TYPE_2__ {int chroma_xs; int chroma_ys; int* bpp; } ;
struct mp_image {int num_planes; TYPE_1__ fmt; } ;

/* Variables and functions */
 int SWS_MIN_BYTE_ALIGN ; 

__attribute__((used)) static void get_swscale_alignment(const struct mp_image *img, int *out_xstep,
                                  int *out_ystep)
{
    int sx = (1 << img->fmt.chroma_xs);
    int sy = (1 << img->fmt.chroma_ys);

    for (int p = 0; p < img->num_planes; ++p) {
        int bits = img->fmt.bpp[p];
        // the * 2 fixes problems with writing past the destination width
        while (((sx >> img->fmt.chroma_xs) * bits) % (SWS_MIN_BYTE_ALIGN * 8 * 2))
            sx *= 2;
    }

    *out_xstep = sx;
    *out_ystep = sy;
}