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
struct sock {int sk_rcvbuf; int /*<<< orphan*/  sk_rmem_alloc; } ;
struct sk_buff {size_t data; scalar_t__ len; } ;
struct sctp_ulpevent {int msg_flags; int /*<<< orphan*/  tsn; int /*<<< orphan*/  cumtsn; int /*<<< orphan*/  flags; void* stream; struct sctp_chunk* chunk; } ;
struct TYPE_11__ {TYPE_4__* data_hdr; } ;
struct sctp_chunk {size_t chunk_end; TYPE_6__* chunk_hdr; TYPE_5__ subh; int /*<<< orphan*/  transport; struct sk_buff* skb; } ;
struct TYPE_9__ {int /*<<< orphan*/  tsn_map; } ;
struct TYPE_7__ {struct sock* sk; } ;
struct sctp_association {TYPE_3__ peer; int /*<<< orphan*/  rmem_alloc; TYPE_2__* ep; TYPE_1__ base; } ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_12__ {int flags; int /*<<< orphan*/  length; } ;
struct TYPE_10__ {int /*<<< orphan*/  tsn; int /*<<< orphan*/  stream; } ;
struct TYPE_8__ {scalar_t__ rcvbuf_policy; } ;

/* Variables and functions */
 int SCTP_DATA_UNORDERED ; 
 size_t SCTP_PAD4 (size_t) ; 
 int /*<<< orphan*/  SCTP_UNORDERED ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 void* ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_chunk_hold (struct sctp_chunk*) ; 
 struct sctp_ulpevent* sctp_skb2event (struct sk_buff*) ; 
 int /*<<< orphan*/  sctp_tsnmap_get_ctsn (int /*<<< orphan*/ *) ; 
 scalar_t__ sctp_tsnmap_mark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sctp_ulpevent_init (struct sctp_ulpevent*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sctp_ulpevent_receive_data (struct sctp_ulpevent*,struct sctp_association*) ; 
 int /*<<< orphan*/  sk_rmem_schedule (struct sock*,struct sk_buff*,size_t) ; 
 struct sk_buff* skb_clone (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_trim (struct sk_buff*,size_t) ; 

struct sctp_ulpevent *sctp_ulpevent_make_rcvmsg(struct sctp_association *asoc,
						struct sctp_chunk *chunk,
						gfp_t gfp)
{
	struct sctp_ulpevent *event = NULL;
	struct sk_buff *skb = chunk->skb;
	struct sock *sk = asoc->base.sk;
	size_t padding, datalen;
	int rx_count;

	/*
	 * check to see if we need to make space for this
	 * new skb, expand the rcvbuffer if needed, or drop
	 * the frame
	 */
	if (asoc->ep->rcvbuf_policy)
		rx_count = atomic_read(&asoc->rmem_alloc);
	else
		rx_count = atomic_read(&sk->sk_rmem_alloc);

	datalen = ntohs(chunk->chunk_hdr->length);

	if (rx_count >= sk->sk_rcvbuf || !sk_rmem_schedule(sk, skb, datalen))
		goto fail;

	/* Clone the original skb, sharing the data.  */
	skb = skb_clone(chunk->skb, gfp);
	if (!skb)
		goto fail;

	/* Now that all memory allocations for this chunk succeeded, we
	 * can mark it as received so the tsn_map is updated correctly.
	 */
	if (sctp_tsnmap_mark(&asoc->peer.tsn_map,
			     ntohl(chunk->subh.data_hdr->tsn),
			     chunk->transport))
		goto fail_mark;

	/* First calculate the padding, so we don't inadvertently
	 * pass up the wrong length to the user.
	 *
	 * RFC 2960 - Section 3.2  Chunk Field Descriptions
	 *
	 * The total length of a chunk(including Type, Length and Value fields)
	 * MUST be a multiple of 4 bytes.  If the length of the chunk is not a
	 * multiple of 4 bytes, the sender MUST pad the chunk with all zero
	 * bytes and this padding is not included in the chunk length field.
	 * The sender should never pad with more than 3 bytes.  The receiver
	 * MUST ignore the padding bytes.
	 */
	padding = SCTP_PAD4(datalen) - datalen;

	/* Fixup cloned skb with just this chunks data.  */
	skb_trim(skb, chunk->chunk_end - padding - skb->data);

	/* Embed the event fields inside the cloned skb.  */
	event = sctp_skb2event(skb);

	/* Initialize event with flags 0  and correct length
	 * Since this is a clone of the original skb, only account for
	 * the data of this chunk as other chunks will be accounted separately.
	 */
	sctp_ulpevent_init(event, 0, skb->len + sizeof(struct sk_buff));

	/* And hold the chunk as we need it for getting the IP headers
	 * later in recvmsg
	 */
	sctp_chunk_hold(chunk);
	event->chunk = chunk;

	sctp_ulpevent_receive_data(event, asoc);

	event->stream = ntohs(chunk->subh.data_hdr->stream);
	if (chunk->chunk_hdr->flags & SCTP_DATA_UNORDERED) {
		event->flags |= SCTP_UNORDERED;
		event->cumtsn = sctp_tsnmap_get_ctsn(&asoc->peer.tsn_map);
	}
	event->tsn = ntohl(chunk->subh.data_hdr->tsn);
	event->msg_flags |= chunk->chunk_hdr->flags;

	return event;

fail_mark:
	kfree_skb(skb);
fail:
	return NULL;
}