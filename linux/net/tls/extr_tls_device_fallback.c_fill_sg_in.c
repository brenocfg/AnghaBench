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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct tls_record_info {int /*<<< orphan*/ * frags; } ;
struct tls_offload_context_tx {int /*<<< orphan*/  lock; } ;
struct sk_buff {int len; } ;
struct scatterlist {int length; } ;
typedef  int /*<<< orphan*/  skb_frag_t ;
typedef  int s32 ;
struct TYPE_2__ {int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  __skb_frag_ref (int /*<<< orphan*/ *) ; 
 int ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_frag_off (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_frag_page (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_frag_size (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_to_sgvec (struct sk_buff*,struct scatterlist*,int,int) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_1__* tcp_hdr (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 struct tls_record_info* tls_get_record (struct tls_offload_context_tx*,int,int /*<<< orphan*/ *) ; 
 int tls_record_is_start_marker (struct tls_record_info*) ; 
 int tls_record_start_seq (struct tls_record_info*) ; 

__attribute__((used)) static int fill_sg_in(struct scatterlist *sg_in,
		      struct sk_buff *skb,
		      struct tls_offload_context_tx *ctx,
		      u64 *rcd_sn,
		      s32 *sync_size,
		      int *resync_sgs)
{
	int tcp_payload_offset = skb_transport_offset(skb) + tcp_hdrlen(skb);
	int payload_len = skb->len - tcp_payload_offset;
	u32 tcp_seq = ntohl(tcp_hdr(skb)->seq);
	struct tls_record_info *record;
	unsigned long flags;
	int remaining;
	int i;

	spin_lock_irqsave(&ctx->lock, flags);
	record = tls_get_record(ctx, tcp_seq, rcd_sn);
	if (!record) {
		spin_unlock_irqrestore(&ctx->lock, flags);
		return -EINVAL;
	}

	*sync_size = tcp_seq - tls_record_start_seq(record);
	if (*sync_size < 0) {
		int is_start_marker = tls_record_is_start_marker(record);

		spin_unlock_irqrestore(&ctx->lock, flags);
		/* This should only occur if the relevant record was
		 * already acked. In that case it should be ok
		 * to drop the packet and avoid retransmission.
		 *
		 * There is a corner case where the packet contains
		 * both an acked and a non-acked record.
		 * We currently don't handle that case and rely
		 * on TCP to retranmit a packet that doesn't contain
		 * already acked payload.
		 */
		if (!is_start_marker)
			*sync_size = 0;
		return -EINVAL;
	}

	remaining = *sync_size;
	for (i = 0; remaining > 0; i++) {
		skb_frag_t *frag = &record->frags[i];

		__skb_frag_ref(frag);
		sg_set_page(sg_in + i, skb_frag_page(frag),
			    skb_frag_size(frag), skb_frag_off(frag));

		remaining -= skb_frag_size(frag);

		if (remaining < 0)
			sg_in[i].length += remaining;
	}
	*resync_sgs = i;

	spin_unlock_irqrestore(&ctx->lock, flags);
	if (skb_to_sgvec(skb, &sg_in[i], tcp_payload_offset, payload_len) < 0)
		return -EINVAL;

	return 0;
}