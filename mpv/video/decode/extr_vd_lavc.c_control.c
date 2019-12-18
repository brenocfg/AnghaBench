#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* method_name; } ;
struct TYPE_5__ {int framedrop_flags; TYPE_3__* avctx; int /*<<< orphan*/  use_hwdec; TYPE_1__ hwdec; } ;
typedef  TYPE_2__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_2__* priv; } ;
typedef  enum dec_ctrl { ____Placeholder_dec_ctrl } dec_ctrl ;
struct TYPE_6__ {int has_b_frames; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int CONTROL_ERROR ; 
 int CONTROL_FALSE ; 
 int CONTROL_OK ; 
 int CONTROL_TRUE ; 
 int CONTROL_UNKNOWN ; 
#define  VDCTRL_FORCE_HWDEC_FALLBACK 132 
#define  VDCTRL_GET_BFRAMES 131 
#define  VDCTRL_GET_HWDEC 130 
#define  VDCTRL_REINIT 129 
#define  VDCTRL_SET_FRAMEDROP 128 
 int /*<<< orphan*/  force_fallback (struct mp_filter*) ; 
 int /*<<< orphan*/  reinit (struct mp_filter*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static int control(struct mp_filter *vd, enum dec_ctrl cmd, void *arg)
{
    vd_ffmpeg_ctx *ctx = vd->priv;
    switch (cmd) {
    case VDCTRL_SET_FRAMEDROP:
        ctx->framedrop_flags = *(int *)arg;
        return CONTROL_TRUE;
    case VDCTRL_GET_BFRAMES: {
        AVCodecContext *avctx = ctx->avctx;
        if (!avctx)
            break;
        if (ctx->use_hwdec && strcmp(ctx->hwdec.method_name, "mmal") == 0)
            break; // MMAL has arbitrary buffering, thus unknown
        *(int *)arg = avctx->has_b_frames;
        return CONTROL_TRUE;
    }
    case VDCTRL_GET_HWDEC: {
        *(char **)arg = ctx->use_hwdec ? ctx->hwdec.method_name : NULL;
        return CONTROL_TRUE;
    }
    case VDCTRL_FORCE_HWDEC_FALLBACK:
        if (ctx->use_hwdec) {
            force_fallback(vd);
            return ctx->avctx ? CONTROL_OK : CONTROL_ERROR;
        }
        return CONTROL_FALSE;
    case VDCTRL_REINIT:
        reinit(vd);
        return CONTROL_TRUE;
    }
    return CONTROL_UNKNOWN;
}