#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {unsigned int len; scalar_t__ cb; int /*<<< orphan*/  protocol; int /*<<< orphan*/  dev; } ;
struct TYPE_13__ {int id; int /*<<< orphan*/ * flags; } ;
struct TYPE_14__ {TYPE_4__ l2; } ;
struct qeth_hdr {TYPE_5__ hdr; } ;
struct TYPE_18__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_17__ {int /*<<< orphan*/  (* data_cb ) (struct sk_buff*) ;} ;
struct TYPE_16__ {int /*<<< orphan*/  type; } ;
struct TYPE_15__ {int /*<<< orphan*/  pkt_seqno; } ;
struct TYPE_12__ {size_t b_index; int /*<<< orphan*/  e_offset; int /*<<< orphan*/  b_element; } ;
struct TYPE_11__ {TYPE_1__* in_q; } ;
struct qeth_card {TYPE_9__ stats; TYPE_8__ osn_info; TYPE_7__ info; int /*<<< orphan*/  napi; TYPE_6__ seqno; TYPE_3__ rx; TYPE_2__ qdio; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_10__ {int /*<<< orphan*/ * bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  ETH_P_802_2 ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TYPE_OSN ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_hdr*,int) ; 
#define  QETH_HEADER_TYPE_LAYER2 129 
#define  QETH_HEADER_TYPE_OSN 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 struct sk_buff* qeth_core_get_next_skb (struct qeth_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qeth_hdr**) ; 
 int /*<<< orphan*/  qeth_rx_csum (struct qeth_card*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct qeth_hdr*,int) ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*) ; 

__attribute__((used)) static int qeth_l2_process_inbound_buffer(struct qeth_card *card,
				int budget, int *done)
{
	int work_done = 0;
	struct sk_buff *skb;
	struct qeth_hdr *hdr;
	unsigned int len;

	*done = 0;
	WARN_ON_ONCE(!budget);
	while (budget) {
		skb = qeth_core_get_next_skb(card,
			&card->qdio.in_q->bufs[card->rx.b_index],
			&card->rx.b_element, &card->rx.e_offset, &hdr);
		if (!skb) {
			*done = 1;
			break;
		}
		switch (hdr->hdr.l2.id) {
		case QETH_HEADER_TYPE_LAYER2:
			skb->protocol = eth_type_trans(skb, skb->dev);
			qeth_rx_csum(card, skb, hdr->hdr.l2.flags[1]);
			if (skb->protocol == htons(ETH_P_802_2))
				*((__u32 *)skb->cb) = ++card->seqno.pkt_seqno;
			len = skb->len;
			napi_gro_receive(&card->napi, skb);
			break;
		case QETH_HEADER_TYPE_OSN:
			if (card->info.type == QETH_CARD_TYPE_OSN) {
				skb_push(skb, sizeof(struct qeth_hdr));
				skb_copy_to_linear_data(skb, hdr,
						sizeof(struct qeth_hdr));
				len = skb->len;
				card->osn_info.data_cb(skb);
				break;
			}
			/* else unknown */
		default:
			dev_kfree_skb_any(skb);
			QETH_CARD_TEXT(card, 3, "inbunkno");
			QETH_DBF_HEX(CTRL, 3, hdr, sizeof(*hdr));
			continue;
		}
		work_done++;
		budget--;
		card->stats.rx_packets++;
		card->stats.rx_bytes += len;
	}
	return work_done;
}