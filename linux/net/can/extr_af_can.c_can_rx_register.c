#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct receiver {void (* func ) (struct sk_buff*,void*) ;char* ident; int /*<<< orphan*/  list; struct sock* sk; void* data; scalar_t__ matches; void* mask; void* can_id; } ;
struct net_device {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  rcvlists_lock; struct can_rcv_lists_stats* rcv_lists_stats; } ;
struct net {TYPE_1__ can; } ;
struct hlist_head {int dummy; } ;
struct can_rcv_lists_stats {int /*<<< orphan*/  rcv_entries; int /*<<< orphan*/  rcv_entries_max; } ;
struct can_dev_rcv_lists {int /*<<< orphan*/  entries; } ;
typedef  void* canid_t ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 struct can_dev_rcv_lists* can_dev_rcv_lists_find (struct net*,struct net_device*) ; 
 struct hlist_head* can_rcv_list_find (void**,void**,struct can_dev_rcv_lists*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 
 struct receiver* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_cache ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

int can_rx_register(struct net *net, struct net_device *dev, canid_t can_id,
		    canid_t mask, void (*func)(struct sk_buff *, void *),
		    void *data, char *ident, struct sock *sk)
{
	struct receiver *rcv;
	struct hlist_head *rcv_list;
	struct can_dev_rcv_lists *dev_rcv_lists;
	struct can_rcv_lists_stats *rcv_lists_stats = net->can.rcv_lists_stats;
	int err = 0;

	/* insert new receiver  (dev,canid,mask) -> (func,data) */

	if (dev && dev->type != ARPHRD_CAN)
		return -ENODEV;

	if (dev && !net_eq(net, dev_net(dev)))
		return -ENODEV;

	rcv = kmem_cache_alloc(rcv_cache, GFP_KERNEL);
	if (!rcv)
		return -ENOMEM;

	spin_lock_bh(&net->can.rcvlists_lock);

	dev_rcv_lists = can_dev_rcv_lists_find(net, dev);
	rcv_list = can_rcv_list_find(&can_id, &mask, dev_rcv_lists);

	rcv->can_id = can_id;
	rcv->mask = mask;
	rcv->matches = 0;
	rcv->func = func;
	rcv->data = data;
	rcv->ident = ident;
	rcv->sk = sk;

	hlist_add_head_rcu(&rcv->list, rcv_list);
	dev_rcv_lists->entries++;

	rcv_lists_stats->rcv_entries++;
	rcv_lists_stats->rcv_entries_max = max(rcv_lists_stats->rcv_entries_max,
					       rcv_lists_stats->rcv_entries);
	spin_unlock_bh(&net->can.rcvlists_lock);

	return err;
}