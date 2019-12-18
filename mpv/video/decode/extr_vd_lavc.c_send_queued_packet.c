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
struct TYPE_2__ {int num_requeue_packets; int /*<<< orphan*/ * requeue_packets; int /*<<< orphan*/  hw_probing; } ;
typedef  TYPE_1__ vd_ffmpeg_ctx ;
struct mp_filter {TYPE_1__* priv; } ;

/* Variables and functions */
 scalar_t__ AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  MP_TARRAY_REMOVE_AT (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ send_packet (struct mp_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  talloc_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_queued_packet(struct mp_filter *vd)
{
    vd_ffmpeg_ctx *ctx = vd->priv;

    assert(ctx->num_requeue_packets);
    assert(!ctx->hw_probing);

    if (send_packet(vd, ctx->requeue_packets[0]) != AVERROR(EAGAIN)) {
        talloc_free(ctx->requeue_packets[0]);
        MP_TARRAY_REMOVE_AT(ctx->requeue_packets, ctx->num_requeue_packets, 0);
    }
}