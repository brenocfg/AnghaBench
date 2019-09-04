#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct ra_hwdec {struct priv_owner* priv; } ;
struct priv_owner {int probing_formats; int* formats; TYPE_1__* ctx; } ;
struct TYPE_16__ {int /*<<< orphan*/  hw_subfmt; } ;
struct mp_image {TYPE_5__ params; } ;
struct TYPE_15__ {scalar_t__ data; } ;
struct TYPE_14__ {scalar_t__* valid_sw_formats; } ;
struct TYPE_13__ {scalar_t__ sw_format; int width; int height; int /*<<< orphan*/  format; } ;
struct TYPE_12__ {int /*<<< orphan*/  av_device_ref; } ;
typedef  TYPE_2__ AVHWFramesContext ;
typedef  TYPE_3__ AVHWFramesConstraints ;
typedef  int /*<<< orphan*/  AVFrame ;
typedef  TYPE_4__ AVBufferRef ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_NONE ; 
 int /*<<< orphan*/  AV_PIX_FMT_VAAPI ; 
 int /*<<< orphan*/  MP_TARRAY_APPEND (struct priv_owner*,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct ra_hwdec*,char*,...) ; 
 int /*<<< orphan*/  MP_WARN (struct ra_hwdec*,char*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_4__**) ; 
 int /*<<< orphan*/ * av_frame_alloc () ; 
 int /*<<< orphan*/  av_frame_free (int /*<<< orphan*/ **) ; 
 TYPE_3__* av_hwdevice_get_hwframe_constraints (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_hwframe_constraints_free (TYPE_3__**) ; 
 TYPE_4__* av_hwframe_ctx_alloc (int /*<<< orphan*/ ) ; 
 scalar_t__ av_hwframe_ctx_init (TYPE_4__*) ; 
 scalar_t__ av_hwframe_get_buffer (TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct mp_image* mp_image_from_av_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp_image_params_valid (TYPE_5__*) ; 
 int /*<<< orphan*/  mp_imgfmt_to_name (int) ; 
 int /*<<< orphan*/  talloc_free (struct mp_image*) ; 
 scalar_t__ try_format (struct ra_hwdec*,struct mp_image*) ; 

__attribute__((used)) static void determine_working_formats(struct ra_hwdec *hw)
{
    struct priv_owner *p = hw->priv;
    int num_formats = 0;
    int *formats = NULL;

    p->probing_formats = true;

    AVHWFramesConstraints *fc =
            av_hwdevice_get_hwframe_constraints(p->ctx->av_device_ref, NULL);
    if (!fc) {
        MP_WARN(hw, "failed to retrieve libavutil frame constraints\n");
        goto done;
    }
    for (int n = 0; fc->valid_sw_formats[n] != AV_PIX_FMT_NONE; n++) {
        AVBufferRef *fref = NULL;
        struct mp_image *s = NULL;
        AVFrame *frame = NULL;
        fref = av_hwframe_ctx_alloc(p->ctx->av_device_ref);
        if (!fref)
            goto err;
        AVHWFramesContext *fctx = (void *)fref->data;
        fctx->format = AV_PIX_FMT_VAAPI;
        fctx->sw_format = fc->valid_sw_formats[n];
        fctx->width = 128;
        fctx->height = 128;
        if (av_hwframe_ctx_init(fref) < 0)
            goto err;
        frame = av_frame_alloc();
        if (!frame)
            goto err;
        if (av_hwframe_get_buffer(fref, frame, 0) < 0)
            goto err;
        s = mp_image_from_av_frame(frame);
        if (!s || !mp_image_params_valid(&s->params))
            goto err;
        if (try_format(hw, s))
            MP_TARRAY_APPEND(p, formats, num_formats, s->params.hw_subfmt);
    err:
        talloc_free(s);
        av_frame_free(&frame);
        av_buffer_unref(&fref);
    }
    av_hwframe_constraints_free(&fc);

done:
    MP_TARRAY_APPEND(p, formats, num_formats, 0); // terminate it
    p->formats = formats;
    p->probing_formats = false;

    MP_VERBOSE(hw, "Supported formats:\n");
    for (int n = 0; formats[n]; n++)
        MP_VERBOSE(hw, " %s\n", mp_imgfmt_to_name(formats[n]));
}