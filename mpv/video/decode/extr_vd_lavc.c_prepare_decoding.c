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
struct TYPE_3__ {int framedrop_flags; scalar_t__ hwdec_request_reinit; int /*<<< orphan*/  skip_frame; scalar_t__ intra_only; struct vd_lavc_params* opts; TYPE_2__* avctx; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct vd_lavc_params {int /*<<< orphan*/  framedrop; } ;
struct mp_filter {TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  skip_frame; } ;
typedef  TYPE_2__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVDISCARD_ALL ; 
 int /*<<< orphan*/  AVDISCARD_NONREF ; 
 int /*<<< orphan*/  reset_avctx (struct mp_filter*) ; 

__attribute__((used)) static void prepare_decoding(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;
    AVCodecContext *avctx = ctx->avctx;
    struct vd_lavc_params *opts = ctx->opts;

    if (!avctx)
        return;

    int drop = ctx->framedrop_flags;
    if (drop == 1) {
        avctx->skip_frame = opts->framedrop;    // normal framedrop
    } else if (drop == 2) {
        avctx->skip_frame = AVDISCARD_NONREF;   // hr-seek framedrop
        // Can be much more aggressive for true intra codecs.
        if (ctx->intra_only)
            avctx->skip_frame = AVDISCARD_ALL;
    } else {
        avctx->skip_frame = ctx->skip_frame;    // normal playback
    }

    if (ctx->hwdec_request_reinit)
        reset_avctx(vd);
}