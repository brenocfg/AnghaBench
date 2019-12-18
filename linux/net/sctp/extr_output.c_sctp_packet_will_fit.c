#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u16 ;
struct sctp_packet {size_t size; int ipfragok; size_t overhead; size_t max_size; TYPE_5__* transport; scalar_t__ has_data; TYPE_4__* auth; } ;
struct sctp_chunk {scalar_t__ shkey; scalar_t__ auth; TYPE_1__* chunk_hdr; } ;
typedef  enum sctp_xmit { ____Placeholder_sctp_xmit } sctp_xmit ;
struct TYPE_10__ {size_t pathmtu; int burst_limited; int cwnd; TYPE_2__* asoc; } ;
struct TYPE_9__ {scalar_t__ shkey; TYPE_3__* skb; } ;
struct TYPE_8__ {int /*<<< orphan*/  len; } ;
struct TYPE_7__ {size_t pathmtu; } ;
struct TYPE_6__ {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ SCTP_CID_AUTH ; 
 scalar_t__ SCTP_PAD4 (int /*<<< orphan*/ ) ; 
 int SCTP_XMIT_OK ; 
 int SCTP_XMIT_PMTU_FULL ; 
 int /*<<< orphan*/  sctp_chunk_is_data (struct sctp_chunk*) ; 
 scalar_t__ sctp_packet_empty (struct sctp_packet*) ; 

__attribute__((used)) static enum sctp_xmit sctp_packet_will_fit(struct sctp_packet *packet,
					   struct sctp_chunk *chunk,
					   u16 chunk_len)
{
	enum sctp_xmit retval = SCTP_XMIT_OK;
	size_t psize, pmtu, maxsize;

	/* Don't bundle in this packet if this chunk's auth key doesn't
	 * match other chunks already enqueued on this packet. Also,
	 * don't bundle the chunk with auth key if other chunks in this
	 * packet don't have auth key.
	 */
	if ((packet->auth && chunk->shkey != packet->auth->shkey) ||
	    (!packet->auth && chunk->shkey &&
	     chunk->chunk_hdr->type != SCTP_CID_AUTH))
		return SCTP_XMIT_PMTU_FULL;

	psize = packet->size;
	if (packet->transport->asoc)
		pmtu = packet->transport->asoc->pathmtu;
	else
		pmtu = packet->transport->pathmtu;

	/* Decide if we need to fragment or resubmit later. */
	if (psize + chunk_len > pmtu) {
		/* It's OK to fragment at IP level if any one of the following
		 * is true:
		 *	1. The packet is empty (meaning this chunk is greater
		 *	   the MTU)
		 *	2. The packet doesn't have any data in it yet and data
		 *	   requires authentication.
		 */
		if (sctp_packet_empty(packet) ||
		    (!packet->has_data && chunk->auth)) {
			/* We no longer do re-fragmentation.
			 * Just fragment at the IP layer, if we
			 * actually hit this condition
			 */
			packet->ipfragok = 1;
			goto out;
		}

		/* Similarly, if this chunk was built before a PMTU
		 * reduction, we have to fragment it at IP level now. So
		 * if the packet already contains something, we need to
		 * flush.
		 */
		maxsize = pmtu - packet->overhead;
		if (packet->auth)
			maxsize -= SCTP_PAD4(packet->auth->skb->len);
		if (chunk_len > maxsize)
			retval = SCTP_XMIT_PMTU_FULL;

		/* It is also okay to fragment if the chunk we are
		 * adding is a control chunk, but only if current packet
		 * is not a GSO one otherwise it causes fragmentation of
		 * a large frame. So in this case we allow the
		 * fragmentation by forcing it to be in a new packet.
		 */
		if (!sctp_chunk_is_data(chunk) && packet->has_data)
			retval = SCTP_XMIT_PMTU_FULL;

		if (psize + chunk_len > packet->max_size)
			/* Hit GSO/PMTU limit, gotta flush */
			retval = SCTP_XMIT_PMTU_FULL;

		if (!packet->transport->burst_limited &&
		    psize + chunk_len > (packet->transport->cwnd >> 1))
			/* Do not allow a single GSO packet to use more
			 * than half of cwnd.
			 */
			retval = SCTP_XMIT_PMTU_FULL;

		if (packet->transport->burst_limited &&
		    psize + chunk_len > (packet->transport->burst_limited >> 1))
			/* Do not allow a single GSO packet to use more
			 * than half of original cwnd.
			 */
			retval = SCTP_XMIT_PMTU_FULL;
		/* Otherwise it will fit in the GSO packet */
	}

out:
	return retval;
}