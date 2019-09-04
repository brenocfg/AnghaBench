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
struct net_device {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static void bnep_net_set_mc_list(struct net_device *dev)
{
#ifdef CONFIG_BT_BNEP_MC_FILTER
	struct bnep_session *s = netdev_priv(dev);
	struct sock *sk = s->sock->sk;
	struct bnep_set_filter_req *r;
	struct sk_buff *skb;
	int size;

	BT_DBG("%s mc_count %d", dev->name, netdev_mc_count(dev));

	size = sizeof(*r) + (BNEP_MAX_MULTICAST_FILTERS + 1) * ETH_ALEN * 2;
	skb  = alloc_skb(size, GFP_ATOMIC);
	if (!skb) {
		BT_ERR("%s Multicast list allocation failed", dev->name);
		return;
	}

	r = (void *) skb->data;
	__skb_put(skb, sizeof(*r));

	r->type = BNEP_CONTROL;
	r->ctrl = BNEP_FILTER_MULTI_ADDR_SET;

	if (dev->flags & (IFF_PROMISC | IFF_ALLMULTI)) {
		u8 start[ETH_ALEN] = { 0x01 };

		/* Request all addresses */
		__skb_put_data(skb, start, ETH_ALEN);
		__skb_put_data(skb, dev->broadcast, ETH_ALEN);
		r->len = htons(ETH_ALEN * 2);
	} else {
		struct netdev_hw_addr *ha;
		int i, len = skb->len;

		if (dev->flags & IFF_BROADCAST) {
			__skb_put_data(skb, dev->broadcast, ETH_ALEN);
			__skb_put_data(skb, dev->broadcast, ETH_ALEN);
		}

		/* FIXME: We should group addresses here. */

		i = 0;
		netdev_for_each_mc_addr(ha, dev) {
			if (i == BNEP_MAX_MULTICAST_FILTERS)
				break;
			__skb_put_data(skb, ha->addr, ETH_ALEN);
			__skb_put_data(skb, ha->addr, ETH_ALEN);

			i++;
		}
		r->len = htons(skb->len - len);
	}

	skb_queue_tail(&sk->sk_write_queue, skb);
	wake_up_interruptible(sk_sleep(sk));
#endif
}