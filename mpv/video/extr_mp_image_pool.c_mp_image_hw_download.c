#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mp_image_pool {int dummy; } ;
struct mp_image {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_2__* hwctx; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  TYPE_1__ AVHWFramesContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ *) ; 
 int av_hwframe_transfer_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_copy_attributes (struct mp_image*,struct mp_image*) ; 
 struct mp_image* mp_image_from_av_frame (int /*<<< orphan*/ *) ; 
 int mp_image_hw_download_get_sw_format (struct mp_image*) ; 
 struct mp_image* mp_image_pool_get (struct mp_image_pool*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mp_image_to_av_frame (struct mp_image*) ; 
 int /*<<< orphan*/ * mp_image_to_av_frame_and_unref (struct mp_image*) ; 
 int /*<<< orphan*/  mp_image_unrefp (struct mp_image**) ; 

struct mp_image *mp_image_hw_download(struct mp_image *src,
                                      struct mp_image_pool *swpool)
{
    int imgfmt = mp_image_hw_download_get_sw_format(src);
    if (!imgfmt)
        return NULL;

    assert(src->hwctx);
    AVHWFramesContext *fctx = (void *)src->hwctx->data;

    struct mp_image *dst =
        mp_image_pool_get(swpool, imgfmt, fctx->width, fctx->height);
    if (!dst)
        return NULL;

    // Target image must be writable, so unref it.
    AVFrame *dstav = mp_image_to_av_frame_and_unref(dst);
    if (!dstav)
        return NULL;

    AVFrame *srcav = mp_image_to_av_frame(src);
    if (!srcav) {
        av_frame_unref(dstav);
        return NULL;
    }

    int res = av_hwframe_transfer_data(dstav, srcav, 0);
    av_frame_free(&srcav);
    dst = mp_image_from_av_frame(dstav);
    av_frame_free(&dstav);
    if (res >= 0 && dst) {
        mp_image_set_size(dst, src->w, src->h);
        mp_image_copy_attributes(dst, src);
    } else {
        mp_image_unrefp(&dst);
    }
    return dst;
}