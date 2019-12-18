#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sctp_packet {int /*<<< orphan*/  vtag; } ;
struct TYPE_6__ {int /*<<< orphan*/  sk; } ;
struct sctp_endpoint {TYPE_3__ base; } ;
struct sctp_chunk {TYPE_2__* skb; TYPE_1__* sctp_hdr; } ;
struct sctp_association {int dummy; } ;
struct net {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  sk; } ;
struct TYPE_4__ {int /*<<< orphan*/  vtag; } ;

/* Variables and functions */
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_addto_chunk (struct sctp_chunk*,size_t,void const*) ; 
 struct sctp_chunk* sctp_make_abort (struct sctp_association const*,struct sctp_chunk*,size_t) ; 
 int /*<<< orphan*/  sctp_ootb_pkt_free (struct sctp_packet*) ; 
 struct sctp_packet* sctp_ootb_pkt_new (struct net*,struct sctp_association const*,struct sctp_chunk*) ; 
 int /*<<< orphan*/  sctp_packet_append_chunk (struct sctp_packet*,struct sctp_chunk*) ; 
 scalar_t__ sctp_test_T_bit (struct sctp_chunk*) ; 

__attribute__((used)) static struct sctp_packet *sctp_abort_pkt_new(
					struct net *net,
					const struct sctp_endpoint *ep,
					const struct sctp_association *asoc,
					struct sctp_chunk *chunk,
					const void *payload, size_t paylen)
{
	struct sctp_packet *packet;
	struct sctp_chunk *abort;

	packet = sctp_ootb_pkt_new(net, asoc, chunk);

	if (packet) {
		/* Make an ABORT.
		 * The T bit will be set if the asoc is NULL.
		 */
		abort = sctp_make_abort(asoc, chunk, paylen);
		if (!abort) {
			sctp_ootb_pkt_free(packet);
			return NULL;
		}

		/* Reflect vtag if T-Bit is set */
		if (sctp_test_T_bit(abort))
			packet->vtag = ntohl(chunk->sctp_hdr->vtag);

		/* Add specified error causes, i.e., payload, to the
		 * end of the chunk.
		 */
		sctp_addto_chunk(abort, paylen, payload);

		/* Set the skb to the belonging sock for accounting.  */
		abort->skb->sk = ep->base.sk;

		sctp_packet_append_chunk(packet, abort);

	}

	return packet;
}