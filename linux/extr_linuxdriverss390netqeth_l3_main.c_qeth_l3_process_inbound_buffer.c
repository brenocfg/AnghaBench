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
struct sk_buff {unsigned int len; int /*<<< orphan*/  dev; int /*<<< orphan*/  protocol; scalar_t__ data; } ;
struct TYPE_13__ {int id; } ;
struct TYPE_14__ {TYPE_4__ l3; } ;
struct qeth_hdr {TYPE_5__ hdr; } ;
struct TYPE_17__ {unsigned int rx_bytes; int /*<<< orphan*/  rx_packets; } ;
struct TYPE_15__ {int /*<<< orphan*/  type; } ;
struct TYPE_12__ {size_t b_index; int /*<<< orphan*/  e_offset; int /*<<< orphan*/  b_element; } ;
struct TYPE_11__ {TYPE_1__* in_q; } ;
struct qeth_card {TYPE_8__ stats; int /*<<< orphan*/  napi; TYPE_9__* dev; TYPE_6__ info; TYPE_3__ rx; TYPE_2__ qdio; } ;
typedef  int /*<<< orphan*/  __u16 ;
struct TYPE_18__ {int /*<<< orphan*/  dev_addr; TYPE_7__* header_ops; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* create ) (struct sk_buff*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ;} ;
struct TYPE_10__ {int /*<<< orphan*/ * bufs; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTRL ; 
 int /*<<< orphan*/  ETH_P_AF_IUCV ; 
 int /*<<< orphan*/  QETH_CARD_TEXT (struct qeth_card*,int,char*) ; 
 int /*<<< orphan*/  QETH_CARD_TYPE_IQD ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,struct qeth_hdr*,int) ; 
#define  QETH_HEADER_TYPE_LAYER2 129 
#define  QETH_HEADER_TYPE_LAYER3 128 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  napi_gro_receive (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  netif_receive_skb (struct sk_buff*) ; 
 struct sk_buff* qeth_core_get_next_skb (struct qeth_card*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct qeth_hdr**) ; 
 int /*<<< orphan*/  qeth_l3_rebuild_skb (struct qeth_card*,struct sk_buff*,struct qeth_hdr*) ; 
 int /*<<< orphan*/  skb_reset_mac_header (struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sk_buff*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,unsigned int) ; 

__attribute__((used)) static int qeth_l3_process_inbound_buffer(struct qeth_card *card,
				int budget, int *done)
{
	int work_done = 0;
	struct sk_buff *skb;
	struct qeth_hdr *hdr;
	unsigned int len;
	__u16 magic;

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
		switch (hdr->hdr.l3.id) {
		case QETH_HEADER_TYPE_LAYER3:
			magic = *(__u16 *)skb->data;
			if ((card->info.type == QETH_CARD_TYPE_IQD) &&
			    (magic == ETH_P_AF_IUCV)) {
				skb->protocol = cpu_to_be16(ETH_P_AF_IUCV);
				len = skb->len;
				card->dev->header_ops->create(skb, card->dev, 0,
					card->dev->dev_addr, "FAKELL", len);
				skb_reset_mac_header(skb);
				netif_receive_skb(skb);
			} else {
				qeth_l3_rebuild_skb(card, skb, hdr);
				len = skb->len;
				napi_gro_receive(&card->napi, skb);
			}
			break;
		case QETH_HEADER_TYPE_LAYER2: /* for HiperSockets sniffer */
			skb->protocol = eth_type_trans(skb, skb->dev);
			len = skb->len;
			netif_receive_skb(skb);
			break;
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