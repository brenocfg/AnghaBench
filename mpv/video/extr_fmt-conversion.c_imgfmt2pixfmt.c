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
struct TYPE_2__ {int fmt; int pix_fmt; } ;

/* Variables and functions */
 int AV_PIX_FMT_NONE ; 
 int IMGFMT_AVPIXFMT_END ; 
 int IMGFMT_AVPIXFMT_START ; 
 int IMGFMT_NONE ; 
 scalar_t__ av_pix_fmt_desc_get (int) ; 
 TYPE_1__* conversion_map ; 
 int pixfmt2imgfmt (int) ; 

enum AVPixelFormat imgfmt2pixfmt(int fmt)
{
    if (fmt == IMGFMT_NONE)
        return AV_PIX_FMT_NONE;

    if (fmt >= IMGFMT_AVPIXFMT_START && fmt < IMGFMT_AVPIXFMT_END) {
        enum AVPixelFormat pixfmt = fmt - IMGFMT_AVPIXFMT_START;
        // Avoid duplicate format - each format must be unique.
        int mpfmt = pixfmt2imgfmt(pixfmt);
        if (mpfmt == fmt && av_pix_fmt_desc_get(pixfmt))
            return pixfmt;
        return AV_PIX_FMT_NONE;
    }

    for (int i = 0; conversion_map[i].fmt; i++) {
        if (conversion_map[i].fmt == fmt)
            return conversion_map[i].pix_fmt;
    }
    return AV_PIX_FMT_NONE;
}