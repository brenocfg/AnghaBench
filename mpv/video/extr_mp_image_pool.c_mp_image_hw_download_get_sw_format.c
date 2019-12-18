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
struct mp_image {int /*<<< orphan*/  hwctx; } ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;

/* Variables and functions */
 int /*<<< orphan*/  AV_HWFRAME_TRANSFER_DIRECTION_FROM ; 
 int AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  av_free (int*) ; 
 scalar_t__ av_hwframe_transfer_get_formats (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int**,int /*<<< orphan*/ ) ; 
 int pixfmt2imgfmt (int) ; 

int mp_image_hw_download_get_sw_format(struct mp_image *src)
{
    if (!src->hwctx)
        return 0;

    // Try to find the first format which we can apparently use.
    int imgfmt = 0;
    enum AVPixelFormat *fmts;
    if (av_hwframe_transfer_get_formats(src->hwctx,
            AV_HWFRAME_TRANSFER_DIRECTION_FROM, &fmts, 0) < 0)
        return 0;
    for (int n = 0; fmts[n] != AV_PIX_FMT_NONE; n++) {
        imgfmt = pixfmt2imgfmt(fmts[n]);
        if (imgfmt)
            break;
    }
    av_free(fmts);

    return imgfmt;
}