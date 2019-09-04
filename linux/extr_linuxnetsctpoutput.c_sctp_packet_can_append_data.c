#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sctp_transport {size_t flight_size; size_t cwnd; int pathmtu; struct sctp_association* asoc; } ;
struct sctp_packet {int overhead; struct sctp_transport* transport; } ;
struct sctp_outq {size_t outstanding_bytes; int out_qlen; } ;
struct sctp_chunk {scalar_t__ fast_retransmit; TYPE_5__* msg; TYPE_4__* asoc; TYPE_3__* skb; } ;
struct TYPE_8__ {int /*<<< orphan*/  sk; } ;
struct TYPE_7__ {size_t rwnd; } ;
struct sctp_association {int /*<<< orphan*/  force_delay; TYPE_2__ base; TYPE_1__ peer; struct sctp_outq outqueue; } ;
typedef  enum sctp_xmit { ____Placeholder_sctp_xmit } sctp_xmit ;
struct TYPE_12__ {scalar_t__ nodelay; } ;
struct TYPE_11__ {int /*<<< orphan*/  can_delay; } ;
struct TYPE_10__ {int /*<<< orphan*/  stream; } ;
struct TYPE_9__ {int len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESTABLISHED ; 
 scalar_t__ SCTP_NEED_FRTX ; 
 int SCTP_XMIT_DELAY ; 
 int SCTP_XMIT_OK ; 
 int SCTP_XMIT_RWND_FULL ; 
 size_t sctp_data_size (struct sctp_chunk*) ; 
 int sctp_datachk_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sctp_packet_empty (struct sctp_packet*) ; 
 TYPE_6__* sctp_sk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_state (struct sctp_association*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static enum sctp_xmit sctp_packet_can_append_data(struct sctp_packet *packet,
						  struct sctp_chunk *chunk)
{
	size_t datasize, rwnd, inflight, flight_size;
	struct sctp_transport *transport = packet->transport;
	struct sctp_association *asoc = transport->asoc;
	struct sctp_outq *q = &asoc->outqueue;

	/* RFC 2960 6.1  Transmission of DATA Chunks
	 *
	 * A) At any given time, the data sender MUST NOT transmit new data to
	 * any destination transport address if its peer's rwnd indicates
	 * that the peer has no buffer space (i.e. rwnd is 0, see Section
	 * 6.2.1).  However, regardless of the value of rwnd (including if it
	 * is 0), the data sender can always have one DATA chunk in flight to
	 * the receiver if allowed by cwnd (see rule B below).  This rule
	 * allows the sender to probe for a change in rwnd that the sender
	 * missed due to the SACK having been lost in transit from the data
	 * receiver to the data sender.
	 */

	rwnd = asoc->peer.rwnd;
	inflight = q->outstanding_bytes;
	flight_size = transport->flight_size;

	datasize = sctp_data_size(chunk);

	if (datasize > rwnd && inflight > 0)
		/* We have (at least) one data chunk in flight,
		 * so we can't fall back to rule 6.1 B).
		 */
		return SCTP_XMIT_RWND_FULL;

	/* RFC 2960 6.1  Transmission of DATA Chunks
	 *
	 * B) At any given time, the sender MUST NOT transmit new data
	 * to a given transport address if it has cwnd or more bytes
	 * of data outstanding to that transport address.
	 */
	/* RFC 7.2.4 & the Implementers Guide 2.8.
	 *
	 * 3) ...
	 *    When a Fast Retransmit is being performed the sender SHOULD
	 *    ignore the value of cwnd and SHOULD NOT delay retransmission.
	 */
	if (chunk->fast_retransmit != SCTP_NEED_FRTX &&
	    flight_size >= transport->cwnd)
		return SCTP_XMIT_RWND_FULL;

	/* Nagle's algorithm to solve small-packet problem:
	 * Inhibit the sending of new chunks when new outgoing data arrives
	 * if any previously transmitted data on the connection remains
	 * unacknowledged.
	 */

	if ((sctp_sk(asoc->base.sk)->nodelay || inflight == 0) &&
	    !asoc->force_delay)
		/* Nothing unacked */
		return SCTP_XMIT_OK;

	if (!sctp_packet_empty(packet))
		/* Append to packet */
		return SCTP_XMIT_OK;

	if (!sctp_state(asoc, ESTABLISHED))
		return SCTP_XMIT_OK;

	/* Check whether this chunk and all the rest of pending data will fit
	 * or delay in hopes of bundling a full sized packet.
	 */
	if (chunk->skb->len + q->out_qlen > transport->pathmtu -
	    packet->overhead - sctp_datachk_len(&chunk->asoc->stream) - 4)
		/* Enough data queued to fill a packet */
		return SCTP_XMIT_OK;

	/* Don't delay large message writes that may have been fragmented */
	if (!chunk->msg->can_delay)
		return SCTP_XMIT_OK;

	/* Defer until all data acked or packet full */
	return SCTP_XMIT_DELAY;
}