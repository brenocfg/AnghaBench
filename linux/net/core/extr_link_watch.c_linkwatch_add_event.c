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
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lweventlist ; 
 int /*<<< orphan*/  lweventlist_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void linkwatch_add_event(struct net_device *dev)
{
	unsigned long flags;

	spin_lock_irqsave(&lweventlist_lock, flags);
	if (list_empty(&dev->link_watch_list)) {
		list_add_tail(&dev->link_watch_list, &lweventlist);
		dev_hold(dev);
	}
	spin_unlock_irqrestore(&lweventlist_lock, flags);
}