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
struct ncsi_package {int /*<<< orphan*/  lock; int /*<<< orphan*/  channel_num; } ;
struct TYPE_3__ {struct ncsi_channel* vids; } ;
struct TYPE_4__ {struct ncsi_channel* addrs; } ;
struct ncsi_channel {int /*<<< orphan*/  node; int /*<<< orphan*/  lock; int /*<<< orphan*/  state; TYPE_1__ vlan_filter; TYPE_2__ mac_filter; struct ncsi_package* package; } ;

/* Variables and functions */
 int /*<<< orphan*/  NCSI_CHANNEL_INACTIVE ; 
 int /*<<< orphan*/  kfree (struct ncsi_channel*) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ncsi_stop_channel_monitor (struct ncsi_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ncsi_remove_channel(struct ncsi_channel *nc)
{
	struct ncsi_package *np = nc->package;
	unsigned long flags;

	spin_lock_irqsave(&nc->lock, flags);

	/* Release filters */
	kfree(nc->mac_filter.addrs);
	kfree(nc->vlan_filter.vids);

	nc->state = NCSI_CHANNEL_INACTIVE;
	spin_unlock_irqrestore(&nc->lock, flags);
	ncsi_stop_channel_monitor(nc);

	/* Remove and free channel */
	spin_lock_irqsave(&np->lock, flags);
	list_del_rcu(&nc->node);
	np->channel_num--;
	spin_unlock_irqrestore(&np->lock, flags);

	kfree(nc);
}