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
struct TYPE_2__ {scalar_t__ hwdec_notified; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct mp_filter {int /*<<< orphan*/  log; TYPE_1__* priv; } ;

/* Variables and functions */
 int MSGL_V ; 
 int MSGL_WARN ; 
 int /*<<< orphan*/  init_avctx (struct mp_filter*) ; 
 int /*<<< orphan*/  mp_msg (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  uninit_avctx (struct mp_filter*) ; 

__attribute__((used)) static void force_fallback(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;

    uninit_avctx(vd);
    int lev = ctx->hwdec_notified ? MSGL_WARN : MSGL_V;
    mp_msg(vd->log, lev, "Falling back to software decoding.\n");
    init_avctx(vd);
}