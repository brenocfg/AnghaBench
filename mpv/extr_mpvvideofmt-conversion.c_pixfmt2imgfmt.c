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
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_2__ {int pix_fmt; int fmt; } ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int IMGFMT_AVPIXFMT_END ; 
 int IMGFMT_AVPIXFMT_START ; 
 int IMGFMT_NONE ; 
 TYPE_1__* conversion_map ; 

int pixfmt2imgfmt(enum AVPixelFormat pix_fmt)
{
    if (pix_fmt == AV_PIX_FMT_NONE)
        return IMGFMT_NONE;

    for (int i = 0; conversion_map[i].pix_fmt != AV_PIX_FMT_NONE; i++) {
        if (conversion_map[i].pix_fmt == pix_fmt)
            return conversion_map[i].fmt;
    }

    int generic = IMGFMT_AVPIXFMT_START + pix_fmt;
    if (generic < IMGFMT_AVPIXFMT_END)
        return generic;

    return 0;
}