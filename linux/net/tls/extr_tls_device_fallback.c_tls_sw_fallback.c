#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct tls_offload_context_tx {int dummy; } ;
struct tls_context {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int len; } ;
struct scatterlist {int dummy; } ;
typedef  int s32 ;

/* Variables and functions */
 int ARRAY_SIZE (struct scatterlist*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int MAX_SKB_FRAGS ; 
 int /*<<< orphan*/  consume_skb (struct sk_buff*) ; 
 scalar_t__ fill_sg_in (struct scatterlist*,struct sk_buff*,struct tls_offload_context_tx*,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  kfree (struct scatterlist*) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct scatterlist* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sg_init_table (struct scatterlist*,int) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 struct sk_buff* skb_get (struct sk_buff*) ; 
 int skb_transport_offset (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 
 struct sk_buff* tls_enc_skb (struct tls_context*,struct scatterlist*,struct scatterlist*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 struct tls_context* tls_get_ctx (struct sock*) ; 
 struct tls_offload_context_tx* tls_offload_ctx_tx (struct tls_context*) ; 

__attribute__((used)) static struct sk_buff *tls_sw_fallback(struct sock *sk, struct sk_buff *skb)
{
	int tcp_payload_offset = skb_transport_offset(skb) + tcp_hdrlen(skb);
	struct tls_context *tls_ctx = tls_get_ctx(sk);
	struct tls_offload_context_tx *ctx = tls_offload_ctx_tx(tls_ctx);
	int payload_len = skb->len - tcp_payload_offset;
	struct scatterlist *sg_in, sg_out[3];
	struct sk_buff *nskb = NULL;
	int sg_in_max_elements;
	int resync_sgs = 0;
	s32 sync_size = 0;
	u64 rcd_sn;

	/* worst case is:
	 * MAX_SKB_FRAGS in tls_record_info
	 * MAX_SKB_FRAGS + 1 in SKB head and frags.
	 */
	sg_in_max_elements = 2 * MAX_SKB_FRAGS + 1;

	if (!payload_len)
		return skb;

	sg_in = kmalloc_array(sg_in_max_elements, sizeof(*sg_in), GFP_ATOMIC);
	if (!sg_in)
		goto free_orig;

	sg_init_table(sg_in, sg_in_max_elements);
	sg_init_table(sg_out, ARRAY_SIZE(sg_out));

	if (fill_sg_in(sg_in, skb, ctx, &rcd_sn, &sync_size, &resync_sgs)) {
		/* bypass packets before kernel TLS socket option was set */
		if (sync_size < 0 && payload_len <= -sync_size)
			nskb = skb_get(skb);
		goto put_sg;
	}

	nskb = tls_enc_skb(tls_ctx, sg_out, sg_in, skb, sync_size, rcd_sn);

put_sg:
	while (resync_sgs)
		put_page(sg_page(&sg_in[--resync_sgs]));
	kfree(sg_in);
free_orig:
	if (nskb)
		consume_skb(skb);
	else
		kfree_skb(skb);
	return nskb;
}