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
struct sk_buff {struct net_device* dev; } ;
struct netdev_queue {int dummy; } ;
struct net_device {int dummy; } ;
struct bpf_prog {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HARD_TX_LOCK (struct net_device*,struct netdev_queue*,int) ; 
 int /*<<< orphan*/  HARD_TX_UNLOCK (struct net_device*,struct netdev_queue*) ; 
 int /*<<< orphan*/  XDP_TX ; 
 scalar_t__ dev_xmit_complete (int) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 struct netdev_queue* netdev_core_pick_tx (struct net_device*,struct sk_buff*,int /*<<< orphan*/ *) ; 
 int netdev_start_xmit (struct sk_buff*,struct net_device*,struct netdev_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_xmit_stopped (struct netdev_queue*) ; 
 int smp_processor_id () ; 
 int /*<<< orphan*/  trace_xdp_exception (struct net_device*,struct bpf_prog*,int /*<<< orphan*/ ) ; 

void generic_xdp_tx(struct sk_buff *skb, struct bpf_prog *xdp_prog)
{
	struct net_device *dev = skb->dev;
	struct netdev_queue *txq;
	bool free_skb = true;
	int cpu, rc;

	txq = netdev_core_pick_tx(dev, skb, NULL);
	cpu = smp_processor_id();
	HARD_TX_LOCK(dev, txq, cpu);
	if (!netif_xmit_stopped(txq)) {
		rc = netdev_start_xmit(skb, dev, txq, 0);
		if (dev_xmit_complete(rc))
			free_skb = false;
	}
	HARD_TX_UNLOCK(dev, txq);
	if (free_skb) {
		trace_xdp_exception(dev, xdp_prog, XDP_TX);
		kfree_skb(skb);
	}
}