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
struct TYPE_2__ {int num_delay_queue; int num_sent_packets; int num_requeue_packets; int /*<<< orphan*/ * requeue_packets; int /*<<< orphan*/ * sent_packets; int /*<<< orphan*/ * delay_queue; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_1__* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  reset_avctx (struct mp_filter*) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flush_all(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;

    for (int n = 0; n < ctx->num_delay_queue; n++)
        talloc_free(ctx->delay_queue[n]);
    ctx->num_delay_queue = 0;

    for (int n = 0; n < ctx->num_sent_packets; n++)
        talloc_free(ctx->sent_packets[n]);
    ctx->num_sent_packets = 0;

    for (int n = 0; n < ctx->num_requeue_packets; n++)
        talloc_free(ctx->requeue_packets[n]);
    ctx->num_requeue_packets = 0;

    reset_avctx(vd);
}