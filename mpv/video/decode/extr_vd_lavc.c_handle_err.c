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
struct TYPE_2__ {scalar_t__ hwdec_fail_count; int hwdec_failed; scalar_t__ use_hwdec; struct vd_lavc_params* opts; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct vd_lavc_params {scalar_t__ software_fallback; } ;
struct mp_filter {TYPE_1__* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_WARN (struct mp_filter*,char*,char*) ; 

__attribute__((used)) static void handle_err(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;
    struct vd_lavc_params *opts = ctx->opts;

    MP_WARN(vd, "Error while decoding frame%s!\n",
            ctx->use_hwdec ? " (hardware decoding)" : "");

    if (ctx->use_hwdec) {
        ctx->hwdec_fail_count += 1;
        if (ctx->hwdec_fail_count >= opts->software_fallback)
            ctx->hwdec_failed = true;
    }
}