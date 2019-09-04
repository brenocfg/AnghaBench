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
struct sk_buff {unsigned int len; scalar_t__ ip_summed; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * flags; } ;
struct TYPE_6__ {TYPE_1__ l2; } ;
struct qeth_hdr {TYPE_2__ hdr; } ;
struct TYPE_8__ {unsigned int buf_elements_sent; int /*<<< orphan*/  sg_skbs_sent; int /*<<< orphan*/  tx_csum; } ;
struct TYPE_7__ {scalar_t__ performance_stats; } ;
struct qeth_card {TYPE_4__ perf_stats; TYPE_3__ options; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int EBUSY ; 
 unsigned int ETH_HLEN ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct qeth_hdr*) ; 
 int qeth_add_hw_header (struct qeth_card*,struct sk_buff*,struct qeth_hdr**,unsigned int const,unsigned int const,unsigned int*) ; 
 int /*<<< orphan*/  qeth_core_header_cache ; 
 int qeth_do_send_packet (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,unsigned int,unsigned int,unsigned int) ; 
 int qeth_do_send_packet_fast (struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  qeth_l2_fill_header (struct qeth_hdr*,struct sk_buff*,int,unsigned int) ; 
 int /*<<< orphan*/  qeth_tx_csum (struct sk_buff*,int /*<<< orphan*/ *,int) ; 
 int skb_cow_head (struct sk_buff*,unsigned int const) ; 
 int skb_is_nonlinear (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_orphan (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int) ; 

__attribute__((used)) static int qeth_l2_xmit(struct qeth_card *card, struct sk_buff *skb,
			struct qeth_qdio_out_q *queue, int cast_type, int ipv)
{
	const unsigned int proto_len = IS_IQD(card) ? ETH_HLEN : 0;
	const unsigned int hw_hdr_len = sizeof(struct qeth_hdr);
	unsigned int frame_len = skb->len;
	unsigned int data_offset = 0;
	struct qeth_hdr *hdr = NULL;
	unsigned int hd_len = 0;
	unsigned int elements;
	int push_len, rc;
	bool is_sg;

	rc = skb_cow_head(skb, hw_hdr_len);
	if (rc)
		return rc;

	push_len = qeth_add_hw_header(card, skb, &hdr, hw_hdr_len, proto_len,
				      &elements);
	if (push_len < 0)
		return push_len;
	if (!push_len) {
		/* HW header needs its own buffer element. */
		hd_len = hw_hdr_len + proto_len;
		data_offset = proto_len;
	}
	qeth_l2_fill_header(hdr, skb, cast_type, frame_len);
	if (skb->ip_summed == CHECKSUM_PARTIAL) {
		qeth_tx_csum(skb, &hdr->hdr.l2.flags[1], ipv);
		if (card->options.performance_stats)
			card->perf_stats.tx_csum++;
	}

	is_sg = skb_is_nonlinear(skb);
	if (IS_IQD(card)) {
		rc = qeth_do_send_packet_fast(queue, skb, hdr, data_offset,
					      hd_len);
	} else {
		/* TODO: drop skb_orphan() once TX completion is fast enough */
		skb_orphan(skb);
		rc = qeth_do_send_packet(card, queue, skb, hdr, data_offset,
					 hd_len, elements);
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
		if (rc == -EBUSY)
			/* roll back to ETH header */
			skb_pull(skb, push_len);
	}
	return rc;
}