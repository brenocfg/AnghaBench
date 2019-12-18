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
struct net_device {int /*<<< orphan*/  unreg_list; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  net_set_todo (struct net_device*) ; 
 int /*<<< orphan*/  rollback_registered (struct net_device*) ; 

void unregister_netdevice_queue(struct net_device *dev, struct list_head *head)
{
	ASSERT_RTNL();

	if (head) {
		list_move_tail(&dev->unreg_list, head);
	} else {
		rollback_registered(dev);
		/* Finish processing unregister after unlock */
		net_set_todo(dev);
	}
}