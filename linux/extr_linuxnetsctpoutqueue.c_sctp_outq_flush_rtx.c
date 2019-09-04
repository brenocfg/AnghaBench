#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sctp_flush_ctx {TYPE_8__* q; TYPE_7__* packet; TYPE_6__* transport; TYPE_5__* asoc; int /*<<< orphan*/  gfp; int /*<<< orphan*/  transport_list; } ;
struct TYPE_17__ {int /*<<< orphan*/  retransmit; } ;
struct TYPE_16__ {scalar_t__ has_cookie_echo; } ;
struct TYPE_15__ {scalar_t__ state; int /*<<< orphan*/  last_time_sent; int /*<<< orphan*/  send_ready; TYPE_7__ packet; } ;
struct TYPE_13__ {TYPE_3__* sk; } ;
struct TYPE_10__ {int /*<<< orphan*/  init_tag; } ;
struct TYPE_11__ {int /*<<< orphan*/  ecn_capable; TYPE_1__ i; TYPE_6__* retran_path; } ;
struct TYPE_14__ {TYPE_4__ base; TYPE_2__ peer; } ;
struct TYPE_12__ {int sk_err; } ;

/* Variables and functions */
 scalar_t__ SCTP_UNCONFIRMED ; 
 int __sctp_outq_flush_rtx (TYPE_8__*,TYPE_7__*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_packet_config (TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_transport_reset_t3_rtx (TYPE_6__*) ; 

__attribute__((used)) static bool sctp_outq_flush_rtx(struct sctp_flush_ctx *ctx,
				int rtx_timeout)
{
	int error, start_timer = 0;

	if (ctx->asoc->peer.retran_path->state == SCTP_UNCONFIRMED)
		return false;

	if (ctx->transport != ctx->asoc->peer.retran_path) {
		/* Switch transports & prepare the packet.  */
		ctx->transport = ctx->asoc->peer.retran_path;
		ctx->packet = &ctx->transport->packet;

		if (list_empty(&ctx->transport->send_ready))
			list_add_tail(&ctx->transport->send_ready,
				      &ctx->transport_list);

		sctp_packet_config(ctx->packet, ctx->asoc->peer.i.init_tag,
				   ctx->asoc->peer.ecn_capable);
	}

	error = __sctp_outq_flush_rtx(ctx->q, ctx->packet, rtx_timeout,
				      &start_timer, ctx->gfp);
	if (error < 0)
		ctx->asoc->base.sk->sk_err = -error;

	if (start_timer) {
		sctp_transport_reset_t3_rtx(ctx->transport);
		ctx->transport->last_time_sent = jiffies;
	}

	/* This can happen on COOKIE-ECHO resend.  Only
	 * one chunk can get bundled with a COOKIE-ECHO.
	 */
	if (ctx->packet->has_cookie_echo)
		return false;

	/* Don't send new data if there is still data
	 * waiting to retransmit.
	 */
	if (!list_empty(&ctx->q->retransmit))
		return false;

	return true;
}