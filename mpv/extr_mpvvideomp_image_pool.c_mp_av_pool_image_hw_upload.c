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
struct mp_image {scalar_t__ h; int /*<<< orphan*/  w; } ;
struct AVBufferRef {int dummy; } ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_hwframe_get_buffer (struct AVBufferRef*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_image_copy_attributes (struct mp_image*,struct mp_image*) ; 
 struct mp_image* mp_image_from_av_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_image_hw_upload (struct mp_image*,struct mp_image*) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 

struct mp_image *mp_av_pool_image_hw_upload(struct AVBufferRef *hw_frames_ctx,
                                            struct mp_image *src)
{
    AVFrame *av_frame = av_frame_alloc();
    if (!av_frame)
        return NULL;
    if (av_hwframe_get_buffer(hw_frames_ctx, av_frame, 0) < 0) {
        av_frame_free(&av_frame);
        return NULL;
    }
    struct mp_image *dst = mp_image_from_av_frame(av_frame);
    av_frame_free(&av_frame);
    if (!dst)
        return NULL;

    if (dst->w < src->w || dst->h < src->h) {
        talloc_free(dst);
        return NULL;
    }

    mp_image_set_size(dst, src->w, src->h);

    if (!mp_image_hw_upload(dst, src)) {
        talloc_free(dst);
        return NULL;
    }

    mp_image_copy_attributes(dst, src);
    return dst;
}