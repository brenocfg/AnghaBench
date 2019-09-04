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
struct sk_buff {int len; } ;
struct qeth_qdio_out_q {int dummy; } ;
struct TYPE_6__ {int tx_bytes; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_packets; int /*<<< orphan*/  tx_carrier_errors; } ;
struct TYPE_5__ {scalar_t__ outbound_start_time; int /*<<< orphan*/  outbound_time; int /*<<< orphan*/  outbound_cnt; } ;
struct TYPE_4__ {scalar_t__ performance_stats; } ;
struct qeth_card {scalar_t__ state; TYPE_3__ stats; TYPE_2__ perf_stats; TYPE_1__ options; int /*<<< orphan*/  lan_online; } ;
struct net_device {struct qeth_card* ml_priv; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 scalar_t__ CARD_STATE_UP ; 
 int EBUSY ; 
 scalar_t__ IS_OSN (struct qeth_card*) ; 
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int qeth_get_ip_version (struct sk_buff*) ; 
 scalar_t__ qeth_get_micros () ; 
 struct qeth_qdio_out_q* qeth_get_tx_queue (struct qeth_card*,struct sk_buff*,int,int) ; 
 int qeth_l2_get_cast_type (struct qeth_card*,struct sk_buff*) ; 
 int qeth_l2_xmit (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*,int,int) ; 
 int qeth_l2_xmit_osn (struct qeth_card*,struct sk_buff*,struct qeth_qdio_out_q*) ; 

__attribute__((used)) static netdev_tx_t qeth_l2_hard_start_xmit(struct sk_buff *skb,
					   struct net_device *dev)
{
	struct qeth_card *card = dev->ml_priv;
	int cast_type = qeth_l2_get_cast_type(card, skb);
	int ipv = qeth_get_ip_version(skb);
	struct qeth_qdio_out_q *queue;
	int tx_bytes = skb->len;
	int rc;

	if ((card->state != CARD_STATE_UP) || !card->lan_online) {
		card->stats.tx_carrier_errors++;
		goto tx_drop;
	}

	queue = qeth_get_tx_queue(card, skb, ipv, cast_type);

	if (card->options.performance_stats) {
		card->perf_stats.outbound_cnt++;
		card->perf_stats.outbound_start_time = qeth_get_micros();
	}
	netif_stop_queue(dev);

	if (IS_OSN(card))
		rc = qeth_l2_xmit_osn(card, skb, queue);
	else
		rc = qeth_l2_xmit(card, skb, queue, cast_type, ipv);

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