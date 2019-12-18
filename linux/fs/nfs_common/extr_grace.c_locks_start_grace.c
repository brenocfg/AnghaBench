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
struct TYPE_2__ {int /*<<< orphan*/  inum; } ;
struct net {TYPE_1__ ns; } ;
struct lock_manager {int /*<<< orphan*/  list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  grace_lock ; 
 int /*<<< orphan*/  grace_net_id ; 
 struct net init_net ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct list_head*) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 struct list_head* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void
locks_start_grace(struct net *net, struct lock_manager *lm)
{
	struct list_head *grace_list = net_generic(net, grace_net_id);

	spin_lock(&grace_lock);
	if (list_empty(&lm->list))
		list_add(&lm->list, grace_list);
	else
		WARN(1, "double list_add attempt detected in net %x %s\n",
		     net->ns.inum, (net == &init_net) ? "(init_net)" : "");
	spin_unlock(&grace_lock);
}