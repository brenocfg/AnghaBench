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
struct priv {int /*<<< orphan*/  hw_pool; int /*<<< orphan*/  av_device_ref; int /*<<< orphan*/  queue; } ;
struct mp_image {int /*<<< orphan*/  h; int /*<<< orphan*/  w; TYPE_1__* hwctx; } ;
struct mp_filter {struct priv* priv; } ;
struct TYPE_4__ {int width; int height; } ;
struct TYPE_3__ {scalar_t__ data; } ;
typedef  TYPE_2__ AVHWFramesContext ;
typedef  int /*<<< orphan*/  AVFrame ;

/* Variables and functions */
 int /*<<< orphan*/  IMGFMT_NV12 ; 
 int /*<<< orphan*/  IMGFMT_VAAPI ; 
 int /*<<< orphan*/  MP_ERR (struct mp_filter*,char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 scalar_t__ av_hwframe_get_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mp_image* mp_image_from_av_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_image_set_size (struct mp_image*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mp_image* mp_refqueue_get_format (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_update_av_hw_frames_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static struct mp_image *alloc_out(struct mp_filter *vf)
{
    struct priv *p = vf->priv;

    struct mp_image *fmt = mp_refqueue_get_format(p->queue);
    if (!fmt || !fmt->hwctx)
        return NULL;

    AVHWFramesContext *hw_frames = (void *)fmt->hwctx->data;
    // VAAPI requires the full surface size to match for input and output.
    int src_w = hw_frames->width;
    int src_h = hw_frames->height;

    if (!mp_update_av_hw_frames_pool(&p->hw_pool, p->av_device_ref,
                                     IMGFMT_VAAPI, IMGFMT_NV12, src_w, src_h))
    {
        MP_ERR(vf, "Failed to create hw pool.\n");
        return NULL;
    }

    AVFrame *av_frame = av_frame_alloc();
    if (!av_frame)
        abort();
    if (av_hwframe_get_buffer(p->hw_pool, av_frame, 0) < 0) {
        MP_ERR(vf, "Failed to allocate frame from hw pool.\n");
        av_frame_free(&av_frame);
        return NULL;
    }
    struct mp_image *img = mp_image_from_av_frame(av_frame);
    av_frame_free(&av_frame);
    if (!img) {
        MP_ERR(vf, "Unknown error.\n");
        return NULL;
    }
    mp_image_set_size(img, fmt->w, fmt->h);
    return img;
}