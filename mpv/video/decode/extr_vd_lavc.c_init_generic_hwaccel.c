#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct mp_filter {struct lavc_ctx* priv; } ;
struct TYPE_12__ {int /*<<< orphan*/  use_hw_frames; } ;
struct lavc_ctx {TYPE_5__* cached_hw_frames_ctx; TYPE_7__* avctx; TYPE_2__* opts; int /*<<< orphan*/  hwdec_dev; TYPE_1__ hwdec; } ;
struct hwcontext_fns {int /*<<< orphan*/  (* refine_hwframes ) (TYPE_5__*) ;} ;
typedef  enum AVPixelFormat { ____Placeholder_AVPixelFormat } AVPixelFormat ;
struct TYPE_17__ {int /*<<< orphan*/  hw_frames_ctx; } ;
struct TYPE_16__ {scalar_t__ data; } ;
struct TYPE_15__ {scalar_t__ sw_format; int initial_pool_size; scalar_t__ format; scalar_t__ width; scalar_t__ height; TYPE_3__* device_ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  type; } ;
struct TYPE_13__ {int hwdec_extra_frames; scalar_t__ hwdec_image_format; } ;
typedef  TYPE_4__ AVHWFramesContext ;
typedef  TYPE_5__ AVBufferRef ;

/* Variables and functions */
 int /*<<< orphan*/  MP_ERR (struct lavc_ctx*,char*) ; 
 int /*<<< orphan*/  MP_VERBOSE (struct lavc_ctx*,char*) ; 
 int /*<<< orphan*/  av_buffer_ref (TYPE_5__*) ; 
 int /*<<< orphan*/  av_buffer_unref (TYPE_5__**) ; 
 scalar_t__ av_hwframe_ctx_init (TYPE_5__*) ; 
 scalar_t__ avcodec_get_hw_frames_parameters (TYPE_7__*,int /*<<< orphan*/ ,int,TYPE_5__**) ; 
 struct hwcontext_fns* hwdec_get_hwcontext_fns (int /*<<< orphan*/ ) ; 
 scalar_t__ imgfmt2pixfmt (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static int init_generic_hwaccel(struct mp_filter *vd, enum AVPixelFormat hw_fmt)
{
    struct lavc_ctx *ctx = vd->priv;
    AVBufferRef *new_frames_ctx = NULL;

    if (!ctx->hwdec.use_hw_frames)
        return 0;

    if (!ctx->hwdec_dev) {
        MP_ERR(ctx, "Missing device context.\n");
        goto error;
    }

    if (avcodec_get_hw_frames_parameters(ctx->avctx,
                                ctx->hwdec_dev, hw_fmt, &new_frames_ctx) < 0)
    {
        MP_VERBOSE(ctx, "Hardware decoding of this stream is unsupported?\n");
        goto error;
    }

    AVHWFramesContext *new_fctx = (void *)new_frames_ctx->data;

    if (ctx->opts->hwdec_image_format)
        new_fctx->sw_format = imgfmt2pixfmt(ctx->opts->hwdec_image_format);

    // 1 surface is already included by libavcodec. The field is 0 if the
    // hwaccel supports dynamic surface allocation.
    if (new_fctx->initial_pool_size)
        new_fctx->initial_pool_size += ctx->opts->hwdec_extra_frames - 1;

    const struct hwcontext_fns *fns =
        hwdec_get_hwcontext_fns(new_fctx->device_ctx->type);

    if (fns && fns->refine_hwframes)
        fns->refine_hwframes(new_frames_ctx);

    // We might be able to reuse a previously allocated frame pool.
    if (ctx->cached_hw_frames_ctx) {
        AVHWFramesContext *old_fctx = (void *)ctx->cached_hw_frames_ctx->data;

        if (new_fctx->format            != old_fctx->format ||
            new_fctx->sw_format         != old_fctx->sw_format ||
            new_fctx->width             != old_fctx->width ||
            new_fctx->height            != old_fctx->height ||
            new_fctx->initial_pool_size != old_fctx->initial_pool_size)
            av_buffer_unref(&ctx->cached_hw_frames_ctx);
    }

    if (!ctx->cached_hw_frames_ctx) {
        if (av_hwframe_ctx_init(new_frames_ctx) < 0) {
            MP_ERR(ctx, "Failed to allocate hw frames.\n");
            goto error;
        }

        ctx->cached_hw_frames_ctx = new_frames_ctx;
        new_frames_ctx = NULL;
    }

    ctx->avctx->hw_frames_ctx = av_buffer_ref(ctx->cached_hw_frames_ctx);
    if (!ctx->avctx->hw_frames_ctx)
        goto error;

    av_buffer_unref(&new_frames_ctx);
    return 0;

error:
    av_buffer_unref(&new_frames_ctx);
    av_buffer_unref(&ctx->cached_hw_frames_ctx);
    return -1;
}