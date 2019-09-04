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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_2__ {int avformat; int* bytes; } ;
struct mp_image {int w; int h; int* stride; scalar_t__* planes; TYPE_1__ fmt; } ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  av_be2ne16 (int /*<<< orphan*/ ) ; 
 int** endian_swaps ; 
 int /*<<< orphan*/  mp_image_make_writeable (struct mp_image*) ; 
 int /*<<< orphan*/  mp_image_setfmt (struct mp_image*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pixfmt2imgfmt (int) ; 

struct mp_image *mp_img_swap_to_native(struct mp_image *img)
{
    int to = AV_PIX_FMT_NONE;
    for (int n = 0; endian_swaps[n][0] != AV_PIX_FMT_NONE; n++) {
        if (endian_swaps[n][0] == img->fmt.avformat)
            to = endian_swaps[n][1];
    }
    if (to == AV_PIX_FMT_NONE || !mp_image_make_writeable(img))
        return img;
    int elems = img->fmt.bytes[0] / 2 * img->w;
    for (int y = 0; y < img->h; y++) {
        uint16_t *p = (uint16_t *)(img->planes[0] + y * img->stride[0]);
        for (int i = 0; i < elems; i++)
            p[i] = av_be2ne16(p[i]);
    }
    mp_image_setfmt(img, pixfmt2imgfmt(to));
    return img;
}