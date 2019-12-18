#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct tipc_subscr {int dummy; } ;
struct TYPE_3__ {struct tipc_subscr s; } ;
struct tipc_subscription {int /*<<< orphan*/  service_list; int /*<<< orphan*/  net; TYPE_1__ evt; } ;
struct tipc_service {int /*<<< orphan*/  lock; int /*<<< orphan*/  service_list; int /*<<< orphan*/  subscriptions; int /*<<< orphan*/  ranges; } ;
struct tipc_net {int /*<<< orphan*/  nametbl_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 scalar_t__ RB_EMPTY_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_init_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree_rcu (struct tipc_service*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rcu ; 
 TYPE_2__ seq ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 struct tipc_net* tipc_net (int /*<<< orphan*/ ) ; 
 struct tipc_service* tipc_service_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tipc_sub_put (struct tipc_subscription*) ; 
 int /*<<< orphan*/  tipc_sub_read (struct tipc_subscr*,int /*<<< orphan*/ ) ; 

void tipc_nametbl_unsubscribe(struct tipc_subscription *sub)
{
	struct tipc_net *tn = tipc_net(sub->net);
	struct tipc_subscr *s = &sub->evt.s;
	u32 type = tipc_sub_read(s, seq.type);
	struct tipc_service *sc;

	spin_lock_bh(&tn->nametbl_lock);
	sc = tipc_service_find(sub->net, type);
	if (!sc)
		goto exit;

	spin_lock_bh(&sc->lock);
	list_del_init(&sub->service_list);
	tipc_sub_put(sub);

	/* Delete service item if no more publications and subscriptions */
	if (RB_EMPTY_ROOT(&sc->ranges) && list_empty(&sc->subscriptions)) {
		hlist_del_init_rcu(&sc->service_list);
		kfree_rcu(sc, rcu);
	}
	spin_unlock_bh(&sc->lock);
exit:
	spin_unlock_bh(&tn->nametbl_lock);
}