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
struct TYPE_2__ {scalar_t__ num_requeue_packets; int /*<<< orphan*/ * requeue_packets; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_1__* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ do_send_packet (struct mp_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool send_queued(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;

    while (ctx->num_requeue_packets && do_send_packet(vd, ctx->requeue_packets[0]))
    {
        talloc_free(ctx->requeue_packets[0]);
        MP_TARRAY_REMOVE_AT(ctx->requeue_packets, ctx->num_requeue_packets, 0);
    }

    return ctx->num_requeue_packets == 0;
}