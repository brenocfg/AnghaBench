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
typedef  int uint8_t ;
typedef  int uint32_t ;
struct mp_image {int h; int** planes; int* stride; int w; } ;

/* Variables and functions */
 int MPMIN (int,int) ; 

__attribute__((used)) static void unpremultiply_and_split_BGR32(struct mp_image *img,
                                          struct mp_image *alpha)
{
    for (int y = 0; y < img->h; ++y) {
        uint32_t *irow = (uint32_t *) &img->planes[0][img->stride[0] * y];
        uint8_t *arow = &alpha->planes[0][alpha->stride[0] * y];
        for (int x = 0; x < img->w; ++x) {
            uint32_t pval = irow[x];
            uint8_t aval = (pval >> 24);
            uint8_t rval = (pval >> 16) & 0xFF;
            uint8_t gval = (pval >> 8) & 0xFF;
            uint8_t bval = pval & 0xFF;
            // multiplied = separate * alpha / 255
            // separate = rint(multiplied * 255 / alpha)
            //          = floor(multiplied * 255 / alpha + 0.5)
            //          = floor((multiplied * 255 + 0.5 * alpha) / alpha)
            //          = floor((multiplied * 255 + floor(0.5 * alpha)) / alpha)
            int div = (int) aval;
            int add = div / 2;
            if (aval) {
                rval = MPMIN(255, (rval * 255 + add) / div);
                gval = MPMIN(255, (gval * 255 + add) / div);
                bval = MPMIN(255, (bval * 255 + add) / div);
                irow[x] = bval + (gval << 8) + (rval << 16) + (aval << 24);
            }
            arow[x] = aval;
        }
    }
}