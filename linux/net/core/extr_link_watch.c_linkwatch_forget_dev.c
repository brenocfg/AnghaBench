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
struct net_device {int /*<<< orphan*/  link_watch_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  linkwatch_do_dev (struct net_device*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lweventlist_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void linkwatch_forget_dev(struct net_device *dev)
{
	unsigned long flags;
	int clean = 0;

	spin_lock_irqsave(&lweventlist_lock, flags);
	if (!list_empty(&dev->link_watch_list)) {
		list_del_init(&dev->link_watch_list);
		clean = 1;
	}
	spin_unlock_irqrestore(&lweventlist_lock, flags);
	if (clean)
		linkwatch_do_dev(dev);
}