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
struct sk_buff {int len; scalar_t__ protocol; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_8__ {int tx_bytes; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_carrier_errors; } ;
struct TYPE_7__ {scalar_t__ outbound_start_time; int /*<<< orphan*/  outbound_time; int /*<<< orphan*/  outbound_cnt; } ;
struct TYPE_6__ {scalar_t__ cq; scalar_t__ performance_stats; scalar_t__ sniffer; } ;
struct TYPE_5__ {int /*<<< orphan*/  broadcast_capable; } ;
struct qeth_card {scalar_t__ state; TYPE_4__ stats; TYPE_3__ perf_stats; TYPE_2__ options; TYPE_1__ info; int /*<<< orphan*/  lan_online; } ;
struct net_device {struct qeth_card* ml_priv; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ CARD_STATE_UP ; 
 int EBUSY ; 
 int /*<<< orphan*/  ETH_P_AF_IUCV ; 
 scalar_t__ IS_IQD (struct qeth_card*) ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 scalar_t__ QETH_CQ_ENABLED ; 
 int RTN_BROADCAST ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int qeth_get_ip_version (struct sk_buff*) ; 
 scalar_t__ qeth_get_micros () ; 
 struct qeth_qdio_out_q* qeth_get_tx_queue (struct qeth_card*,struct sk_buff*,int,int) ; 
 int qeth_l3_get_cast_type (struct sk_buff*) ; 
 int qeth_l3_xmit (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*,int,int) ; 
 int qeth_l3_xmit_offload (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*,int,int) ; 
 int /*<<< orphan*/  skb_is_gso (struct sk_buff*) ; 

__attribute__((used)) static netdev_tx_t qeth_l3_hard_start_xmit(struct sk_buff *skb,
					   struct net_device *dev)
{
	int cast_type = qeth_l3_get_cast_type(skb);
	struct qeth_card *card = dev->ml_priv;
	int ipv = qeth_get_ip_version(skb);
	struct qeth_qdio_out_q *queue;
	int tx_bytes = skb->len;
	int rc;

	if (IS_IQD(card)) {
		if (card->options.sniffer)
			goto tx_drop;
		if ((card->options.cq != QETH_CQ_ENABLED && !ipv) ||
		    (card->options.cq == QETH_CQ_ENABLED &&
		     skb->protocol != htons(ETH_P_AF_IUCV)))
			goto tx_drop;
	}

	if (card->state != CARD_STATE_UP || !card->lan_online) {
		card->stats.tx_carrier_errors++;
		goto tx_drop;
	}

	if (cast_type == RTN_BROADCAST && !card->info.broadcast_capable)
		goto tx_drop;

	queue = qeth_get_tx_queue(card, skb, ipv, cast_type);

	if (card->options.performance_stats) {
		card->perf_stats.outbound_cnt++;
		card->perf_stats.outbound_start_time = qeth_get_micros();
	}
	netif_stop_queue(dev);

	if (IS_IQD(card) || (!skb_is_gso(skb) && ipv == 4))
		rc = qeth_l3_xmit_offload(card, skb, queue, ipv, cast_type);
	else
		rc = qeth_l3_xmit(card, skb, queue, ipv, cast_type);

	if (!rc) {
		card->stats.tx_packets++;
		card->stats.tx_bytes += tx_bytes;
		if (card->options.performance_stats)
			card->perf_stats.outbound_time += qeth_get_micros() -
				card->perf_stats.outbound_start_time;
		netif_wake_queue(dev);
		return NETDEV_TX_OK;
	} else if (rc == -EBUSY) {
		return NETDEV_TX_BUSY;
	} /* else fall through */

tx_drop:
	card->stats.tx_dropped++;
	card->stats.tx_errors++;
	dev_kfree_skb_any(skb);
	netif_wake_queue(dev);
	return NETDEV_TX_OK;
}