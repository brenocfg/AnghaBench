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
struct s_pstats {scalar_t__ rcv_entries; scalar_t__ rcv_entries_max; } ;
struct receiver {void (* func ) (struct sk_buff*,void*) ;char* ident; int /*<<< orphan*/  list; struct sock* sk; void* data; scalar_t__ matches; void* mask; void* can_id; } ;
struct net_device {scalar_t__ type; } ;
struct TYPE_2__ {int /*<<< orphan*/  can_rcvlists_lock; struct s_pstats* can_pstats; } ;
struct net {TYPE_1__ can; } ;
struct hlist_head {int dummy; } ;
struct can_dev_rcv_lists {int /*<<< orphan*/  entries; } ;
typedef  void* canid_t ;

/* Variables and functions */
 scalar_t__ ARPHRD_CAN ; 
 int ENODEV ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 struct can_dev_rcv_lists* find_dev_rcv_lists (struct net*,struct net_device*) ; 
 struct hlist_head* find_rcv_list (void**,void**,struct can_dev_rcv_lists*) ; 
 int /*<<< orphan*/  hlist_add_head_rcu (int /*<<< orphan*/ *,struct hlist_head*) ; 
 struct receiver* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct receiver*) ; 
 int /*<<< orphan*/  net_eq (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcv_cache ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int can_rx_register(struct net *net, struct net_device *dev, canid_t can_id,
		    canid_t mask, void (*func)(struct sk_buff *, void *),
		    void *data, char *ident, struct sock *sk)
{
	struct receiver *r;
	struct hlist_head *rl;
	struct can_dev_rcv_lists *d;
	struct s_pstats *can_pstats = net->can.can_pstats;
	int err = 0;

	/* insert new receiver  (dev,canid,mask) -> (func,data) */

	if (dev && dev->type != ARPHRD_CAN)
		return -ENODEV;

	if (dev && !net_eq(net, dev_net(dev)))
		return -ENODEV;

	r = kmem_cache_alloc(rcv_cache, GFP_KERNEL);
	if (!r)
		return -ENOMEM;

	spin_lock(&net->can.can_rcvlists_lock);

	d = find_dev_rcv_lists(net, dev);
	if (d) {
		rl = find_rcv_list(&can_id, &mask, d);

		r->can_id  = can_id;
		r->mask    = mask;
		r->matches = 0;
		r->func    = func;
		r->data    = data;
		r->ident   = ident;
		r->sk      = sk;

		hlist_add_head_rcu(&r->list, rl);
		d->entries++;

		can_pstats->rcv_entries++;
		if (can_pstats->rcv_entries_max < can_pstats->rcv_entries)
			can_pstats->rcv_entries_max = can_pstats->rcv_entries;
	} else {
		kmem_cache_free(rcv_cache, r);
		err = -ENODEV;
	}

	spin_unlock(&net->can.can_rcvlists_lock);

	return err;
}