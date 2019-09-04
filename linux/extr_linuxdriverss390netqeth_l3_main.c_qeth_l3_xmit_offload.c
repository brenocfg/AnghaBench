#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int len; scalar_t__ protocol; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct qeth_hdr {int dummy; } ;
struct TYPE_4__ {unsigned int buf_elements_sent; int /*<<< orphan*/  sg_skbs_sent; } ;
struct TYPE_3__ {scalar_t__ performance_stats; } ;
struct qeth_card {TYPE_2__ perf_stats; TYPE_1__ options; } ;

/* Variables and functions */
 int EBUSY ; 
 int ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_AF_IUCV ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct qeth_hdr*) ; 
 int qeth_add_hw_header (struct qeth_card*,struct sk_buff*,struct qeth_hdr**,unsigned int const,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  qeth_core_header_cache ; 
 int qeth_do_send_packet (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int qeth_do_send_packet_fast (struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  qeth_l3_fill_af_iucv_hdr (struct qeth_hdr*,struct sk_buff*,unsigned int) ; 
 int /*<<< orphan*/  qeth_l3_fill_header (struct qeth_card*,struct qeth_hdr*,struct sk_buff*,int,int,unsigned int) ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,unsigned char*,int) ; 
 int skb_cow_head (struct sk_buff*,int) ; 
 int skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static int qeth_l3_xmit_offload(struct qeth_card *card, struct sk_buff *skb,
				struct qeth_qdio_out_q *queue, int ipv,
				int cast_type)
{
	const unsigned int hw_hdr_len = sizeof(struct qeth_hdr);
	unsigned int frame_len, elements;
	unsigned char eth_hdr[ETH_HLEN];
	struct qeth_hdr *hdr = NULL;
	unsigned int hd_len = 0;
	int push_len, rc;
	bool is_sg;

	/* re-use the L2 header area for the HW header: */
	rc = skb_cow_head(skb, hw_hdr_len - ETH_HLEN);
	if (rc)
		return rc;
	skb_copy_from_linear_data(skb, eth_hdr, ETH_HLEN);
	skb_pull(skb, ETH_HLEN);
	frame_len = skb->len;

	push_len = qeth_add_hw_header(card, skb, &hdr, hw_hdr_len, 0,
				      &elements);
	if (push_len < 0)
		return push_len;
	if (!push_len) {
		/* hdr was added discontiguous from skb->data */
		hd_len = hw_hdr_len;
	}

	if (skb->protocol == htons(ETH_P_AF_IUCV))
		qeth_l3_fill_af_iucv_hdr(hdr, skb, frame_len);
	else
		qeth_l3_fill_header(card, hdr, skb, ipv, cast_type, frame_len);

	is_sg = skb_is_nonlinear(skb);
	if (IS_IQD(card)) {
		rc = qeth_do_send_packet_fast(queue, skb, hdr, 0, hd_len);
	} else {
		/* TODO: drop skb_orphan() once TX completion is fast enough */
		skb_orphan(skb);
		rc = qeth_do_send_packet(card, queue, skb, hdr, 0, hd_len,
					 elements);
	}

	if (!rc) {
		if (card->options.performance_stats) {
			card->perf_stats.buf_elements_sent += elements;
			if (is_sg)
				card->perf_stats.sg_skbs_sent++;
		}
	} else {
		if (!push_len)
			kmem_cache_free(qeth_core_header_cache, hdr);
		if (rc == -EBUSY) {
			/* roll back to ETH header */
			skb_pull(skb, push_len);
			skb_push(skb, ETH_HLEN);
			skb_copy_to_linear_data(skb, eth_hdr, ETH_HLEN);
		}
	}
	return rc;
}