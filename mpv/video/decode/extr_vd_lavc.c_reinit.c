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
struct TYPE_2__ {int use_hwdec; int /*<<< orphan*/  avctx; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_1__* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  force_fallback (struct mp_filter*) ; 
 int /*<<< orphan*/  init_avctx (struct mp_filter*) ; 
 int /*<<< orphan*/  select_and_set_hwdec (struct mp_filter*) ; 
 int /*<<< orphan*/  uninit_avctx (struct mp_filter*) ; 

__attribute__((used)) static void reinit(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;

    uninit_avctx(vd);

    select_and_set_hwdec(vd);

    bool use_hwdec = ctx->use_hwdec;
    init_avctx(vd);
    if (!ctx->avctx && use_hwdec)
        force_fallback(vd);
}