#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sctp_transport {int state; int /*<<< orphan*/  send_ready; int /*<<< orphan*/  packet; int /*<<< orphan*/  ipaddr; } ;
struct sctp_flush_ctx {struct sctp_transport* transport; TYPE_4__* asoc; int /*<<< orphan*/ * packet; int /*<<< orphan*/  transport_list; } ;
struct sctp_chunk {TYPE_1__* chunk_hdr; int /*<<< orphan*/  dest; struct sctp_transport* transport; } ;
typedef  int /*<<< orphan*/  __u8 ;
struct TYPE_6__ {int /*<<< orphan*/  init_tag; } ;
struct TYPE_7__ {int /*<<< orphan*/  ecn_capable; TYPE_2__ i; struct sctp_transport* active_path; } ;
struct TYPE_8__ {TYPE_3__ peer; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  SCTP_CID_ASCONF_ACK ; 
 int /*<<< orphan*/  SCTP_CID_HEARTBEAT ; 
 int /*<<< orphan*/  SCTP_CID_HEARTBEAT_ACK ; 
#define  SCTP_INACTIVE 130 
#define  SCTP_PF 129 
#define  SCTP_UNCONFIRMED 128 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct sctp_transport* sctp_assoc_lookup_paddr (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_chunk_is_data (struct sctp_chunk*) ; 
 scalar_t__ sctp_cmp_addr_exact (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_packet_config (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_transport_burst_limited (struct sctp_transport*) ; 

__attribute__((used)) static void sctp_outq_select_transport(struct sctp_flush_ctx *ctx,
				       struct sctp_chunk *chunk)
{
	struct sctp_transport *new_transport = chunk->transport;

	if (!new_transport) {
		if (!sctp_chunk_is_data(chunk)) {
			/* If we have a prior transport pointer, see if
			 * the destination address of the chunk
			 * matches the destination address of the
			 * current transport.  If not a match, then
			 * try to look up the transport with a given
			 * destination address.  We do this because
			 * after processing ASCONFs, we may have new
			 * transports created.
			 */
			if (ctx->transport && sctp_cmp_addr_exact(&chunk->dest,
							&ctx->transport->ipaddr))
				new_transport = ctx->transport;
			else
				new_transport = sctp_assoc_lookup_paddr(ctx->asoc,
								  &chunk->dest);
		}

		/* if we still don't have a new transport, then
		 * use the current active path.
		 */
		if (!new_transport)
			new_transport = ctx->asoc->peer.active_path;
	} else {
		__u8 type;

		switch (new_transport->state) {
		case SCTP_INACTIVE:
		case SCTP_UNCONFIRMED:
		case SCTP_PF:
			/* If the chunk is Heartbeat or Heartbeat Ack,
			 * send it to chunk->transport, even if it's
			 * inactive.
			 *
			 * 3.3.6 Heartbeat Acknowledgement:
			 * ...
			 * A HEARTBEAT ACK is always sent to the source IP
			 * address of the IP datagram containing the
			 * HEARTBEAT chunk to which this ack is responding.
			 * ...
			 *
			 * ASCONF_ACKs also must be sent to the source.
			 */
			type = chunk->chunk_hdr->type;
			if (type != SCTP_CID_HEARTBEAT &&
			    type != SCTP_CID_HEARTBEAT_ACK &&
			    type != SCTP_CID_ASCONF_ACK)
				new_transport = ctx->asoc->peer.active_path;
			break;
		default:
			break;
		}
	}

	/* Are we switching transports? Take care of transport locks. */
	if (new_transport != ctx->transport) {
		ctx->transport = new_transport;
		ctx->packet = &ctx->transport->packet;

		if (list_empty(&ctx->transport->send_ready))
			list_add_tail(&ctx->transport->send_ready,
				      &ctx->transport_list);

		sctp_packet_config(ctx->packet,
				   ctx->asoc->peer.i.init_tag,
				   ctx->asoc->peer.ecn_capable);
		/* We've switched transports, so apply the
		 * Burst limit to the new transport.
		 */
		sctp_transport_burst_limited(ctx->transport);
	}
}