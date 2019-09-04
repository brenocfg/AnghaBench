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
struct sk_buff {int len; scalar_t__ data; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct qeth_hdr_tso {int dummy; } ;
struct qeth_hdr_layer3 {int dummy; } ;
struct qeth_hdr {int dummy; } ;
struct TYPE_5__ {int buf_elements_sent; int large_send_bytes; int /*<<< orphan*/  large_send_cnt; int /*<<< orphan*/  sg_skbs_sent; int /*<<< orphan*/  tx_lin; int /*<<< orphan*/  tx_linfail; } ;
struct TYPE_4__ {scalar_t__ performance_stats; } ;
struct qeth_card {TYPE_2__ perf_stats; TYPE_1__ options; } ;
typedef  int /*<<< orphan*/  __be16 ;
struct TYPE_6__ {int gso_type; } ;

/* Variables and functions */
 int E2BIG ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_HLEN ; 
 int /*<<< orphan*/  ETH_P_8021Q ; 
 int SKB_GSO_TCPV4 ; 
 int VLAN_HLEN ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int ip_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (struct qeth_hdr*,int /*<<< orphan*/ ,int) ; 
 int qeth_do_send_packet (struct qeth_card*,struct qeth_qdio_out_q*,struct sk_buff*,struct qeth_hdr*,unsigned int,unsigned int,int) ; 
 int qeth_get_elements_no (struct qeth_card*,struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ qeth_hdr_chk_and_bounce (struct sk_buff*,struct qeth_hdr**,int) ; 
 int /*<<< orphan*/  qeth_l3_fill_header (struct qeth_card*,struct qeth_hdr*,struct sk_buff*,int,int,int) ; 
 int qeth_l3_get_elements_no_tso (struct qeth_card*,struct sk_buff*,int) ; 
 int /*<<< orphan*/  qeth_tso_fill_header (struct qeth_card*,struct qeth_hdr*,struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,scalar_t__,int) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,scalar_t__,int) ; 
 scalar_t__ skb_is_gso (struct sk_buff*) ; 
 int skb_is_nonlinear (struct sk_buff*) ; 
 int skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 struct qeth_hdr* skb_push (struct sk_buff*,int) ; 
 struct sk_buff* skb_realloc_headroom (struct sk_buff*,int) ; 
 TYPE_3__* skb_shinfo (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_vlan_tag_get (struct sk_buff*) ; 
 scalar_t__ skb_vlan_tag_present (struct sk_buff*) ; 
 int tcp_hdrlen (struct sk_buff*) ; 

__attribute__((used)) static int qeth_l3_xmit(struct qeth_card *card, struct sk_buff *skb,
			struct qeth_qdio_out_q *queue, int ipv, int cast_type)
{
	int elements, len, rc;
	__be16 *tag;
	struct qeth_hdr *hdr = NULL;
	int hdr_elements = 0;
	struct sk_buff *new_skb = NULL;
	int tx_bytes = skb->len;
	unsigned int hd_len;
	bool use_tso, is_sg;

	/* Ignore segment size from skb_is_gso(), 1 page is always used. */
	use_tso = skb_is_gso(skb) &&
		  (skb_shinfo(skb)->gso_type & SKB_GSO_TCPV4);

	/* create a clone with writeable headroom */
	new_skb = skb_realloc_headroom(skb, sizeof(struct qeth_hdr_tso) +
					    VLAN_HLEN);
	if (!new_skb)
		return -ENOMEM;

	if (ipv == 4) {
		skb_pull(new_skb, ETH_HLEN);
	} else if (skb_vlan_tag_present(new_skb)) {
		skb_push(new_skb, VLAN_HLEN);
		skb_copy_to_linear_data(new_skb, new_skb->data + 4, 4);
		skb_copy_to_linear_data_offset(new_skb, 4,
					       new_skb->data + 8, 4);
		skb_copy_to_linear_data_offset(new_skb, 8,
					       new_skb->data + 12, 4);
		tag = (__be16 *)(new_skb->data + 12);
		*tag = cpu_to_be16(ETH_P_8021Q);
		*(tag + 1) = cpu_to_be16(skb_vlan_tag_get(new_skb));
	}

	/* fix hardware limitation: as long as we do not have sbal
	 * chaining we can not send long frag lists
	 */
	if ((use_tso && !qeth_l3_get_elements_no_tso(card, new_skb, 1)) ||
	    (!use_tso && !qeth_get_elements_no(card, new_skb, 0, 0))) {
		rc = skb_linearize(new_skb);

		if (card->options.performance_stats) {
			if (rc)
				card->perf_stats.tx_linfail++;
			else
				card->perf_stats.tx_lin++;
		}
		if (rc)
			goto out;
	}

	if (use_tso) {
		hdr = skb_push(new_skb, sizeof(struct qeth_hdr_tso));
		memset(hdr, 0, sizeof(struct qeth_hdr_tso));
		qeth_l3_fill_header(card, hdr, new_skb, ipv, cast_type,
				    new_skb->len - sizeof(struct qeth_hdr_tso));
		qeth_tso_fill_header(card, hdr, new_skb);
		hdr_elements++;
	} else {
		hdr = skb_push(new_skb, sizeof(struct qeth_hdr));
		qeth_l3_fill_header(card, hdr, new_skb, ipv, cast_type,
				    new_skb->len - sizeof(struct qeth_hdr));
	}

	elements = use_tso ?
		   qeth_l3_get_elements_no_tso(card, new_skb, hdr_elements) :
		   qeth_get_elements_no(card, new_skb, hdr_elements, 0);
	if (!elements) {
		rc = -E2BIG;
		goto out;
	}
	elements += hdr_elements;

	if (use_tso) {
		hd_len = sizeof(struct qeth_hdr_tso) +
			 ip_hdrlen(new_skb) + tcp_hdrlen(new_skb);
		len = hd_len;
	} else {
		hd_len = 0;
		len = sizeof(struct qeth_hdr_layer3);
	}

	if (qeth_hdr_chk_and_bounce(new_skb, &hdr, len)) {
		rc = -EINVAL;
		goto out;
	}

	is_sg = skb_is_nonlinear(new_skb);
	rc = qeth_do_send_packet(card, queue, new_skb, hdr, hd_len, hd_len,
				 elements);
out:
	if (!rc) {
		if (new_skb != skb)
			dev_kfree_skb_any(skb);
		if (card->options.performance_stats) {
			card->perf_stats.buf_elements_sent += elements;
			if (is_sg)
				card->perf_stats.sg_skbs_sent++;
			if (use_tso) {
				card->perf_stats.large_send_bytes += tx_bytes;
				card->perf_stats.large_send_cnt++;
			}
		}
	} else {
		if (new_skb != skb)
			dev_kfree_skb_any(new_skb);
	}
	return rc;
}