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
struct net_device {int flags; int /*<<< orphan*/  rx_dropped; } ;
struct gro_cells {int /*<<< orphan*/  cells; } ;
struct gro_cell {int /*<<< orphan*/  napi; int /*<<< orphan*/  napi_skbs; } ;

/* Variables and functions */
 int IFF_UP ; 
 int NET_RX_DROP ; 
 int NET_RX_SUCCESS ; 
 int /*<<< orphan*/  __skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  atomic_long_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  napi_schedule (int /*<<< orphan*/ *) ; 
 int netdev_max_backlog ; 
 scalar_t__ netif_elide_gro (struct net_device*) ; 
 int netif_rx (struct sk_buff*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ skb_cloned (struct sk_buff*) ; 
 int skb_queue_len (int /*<<< orphan*/ *) ; 
 struct gro_cell* this_cpu_ptr (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

int gro_cells_receive(struct gro_cells *gcells, struct sk_buff *skb)
{
	struct net_device *dev = skb->dev;
	struct gro_cell *cell;
	int res;

	rcu_read_lock();
	if (unlikely(!(dev->flags & IFF_UP)))
		goto drop;

	if (!gcells->cells || skb_cloned(skb) || netif_elide_gro(dev)) {
		res = netif_rx(skb);
		goto unlock;
	}

	cell = this_cpu_ptr(gcells->cells);

	if (skb_queue_len(&cell->napi_skbs) > netdev_max_backlog) {
drop:
		atomic_long_inc(&dev->rx_dropped);
		kfree_skb(skb);
		res = NET_RX_DROP;
		goto unlock;
	}

	__skb_queue_tail(&cell->napi_skbs, skb);
	if (skb_queue_len(&cell->napi_skbs) == 1)
		napi_schedule(&cell->napi);

	res = NET_RX_SUCCESS;

unlock:
	rcu_read_unlock();
	return res;
}