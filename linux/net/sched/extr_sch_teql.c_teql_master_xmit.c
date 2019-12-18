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
struct teql_master {unsigned int tx_bytes; int /*<<< orphan*/  tx_dropped; int /*<<< orphan*/  tx_errors; struct Qdisc* slaves; int /*<<< orphan*/  tx_packets; } ;
struct sk_buff {int dummy; } ;
struct netdev_queue {struct Qdisc* qdisc_sleeping; } ;
struct net_device {int dummy; } ;
struct Qdisc {int dummy; } ;
typedef  int /*<<< orphan*/  netdev_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  NETDEV_TX_BUSY ; 
 int /*<<< orphan*/  NETDEV_TX_OK ; 
 void* NEXT_SLAVE (struct Qdisc*) ; 
 int /*<<< orphan*/  __netif_tx_trylock (struct netdev_queue*) ; 
 int /*<<< orphan*/  __netif_tx_unlock (struct netdev_queue*) ; 
 int /*<<< orphan*/  __skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_kfree_skb (struct sk_buff*) ; 
 struct netdev_queue* netdev_get_tx_queue (struct net_device*,int) ; 
 struct teql_master* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_start_xmit (struct sk_buff*,struct net_device*,struct netdev_queue*,int) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 int /*<<< orphan*/  netif_stop_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_wake_queue (struct net_device*) ; 
 int /*<<< orphan*/  netif_xmit_frozen_or_stopped (struct netdev_queue*) ; 
 scalar_t__ netif_xmit_stopped (struct netdev_queue*) ; 
 struct net_device* qdisc_dev (struct Qdisc*) ; 
 unsigned int qdisc_pkt_len (struct sk_buff*) ; 
 int skb_get_queue_mapping (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_offset (struct sk_buff*) ; 
 int teql_resolve (struct sk_buff*,struct sk_buff*,struct net_device*,struct netdev_queue*) ; 

__attribute__((used)) static netdev_tx_t teql_master_xmit(struct sk_buff *skb, struct net_device *dev)
{
	struct teql_master *master = netdev_priv(dev);
	struct Qdisc *start, *q;
	int busy;
	int nores;
	int subq = skb_get_queue_mapping(skb);
	struct sk_buff *skb_res = NULL;

	start = master->slaves;

restart:
	nores = 0;
	busy = 0;

	q = start;
	if (!q)
		goto drop;

	do {
		struct net_device *slave = qdisc_dev(q);
		struct netdev_queue *slave_txq = netdev_get_tx_queue(slave, 0);

		if (slave_txq->qdisc_sleeping != q)
			continue;
		if (netif_xmit_stopped(netdev_get_tx_queue(slave, subq)) ||
		    !netif_running(slave)) {
			busy = 1;
			continue;
		}

		switch (teql_resolve(skb, skb_res, slave, slave_txq)) {
		case 0:
			if (__netif_tx_trylock(slave_txq)) {
				unsigned int length = qdisc_pkt_len(skb);

				if (!netif_xmit_frozen_or_stopped(slave_txq) &&
				    netdev_start_xmit(skb, slave, slave_txq, false) ==
				    NETDEV_TX_OK) {
					__netif_tx_unlock(slave_txq);
					master->slaves = NEXT_SLAVE(q);
					netif_wake_queue(dev);
					master->tx_packets++;
					master->tx_bytes += length;
					return NETDEV_TX_OK;
				}
				__netif_tx_unlock(slave_txq);
			}
			if (netif_xmit_stopped(netdev_get_tx_queue(dev, 0)))
				busy = 1;
			break;
		case 1:
			master->slaves = NEXT_SLAVE(q);
			return NETDEV_TX_OK;
		default:
			nores = 1;
			break;
		}
		__skb_pull(skb, skb_network_offset(skb));
	} while ((q = NEXT_SLAVE(q)) != start);

	if (nores && skb_res == NULL) {
		skb_res = skb;
		goto restart;
	}

	if (busy) {
		netif_stop_queue(dev);
		return NETDEV_TX_BUSY;
	}
	master->tx_errors++;

drop:
	master->tx_dropped++;
	dev_kfree_skb(skb);
	return NETDEV_TX_OK;
}