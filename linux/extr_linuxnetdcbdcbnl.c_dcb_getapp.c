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
typedef  int /*<<< orphan*/  u8 ;
struct net_device {int /*<<< orphan*/  ifindex; } ;
struct TYPE_2__ {int /*<<< orphan*/  priority; } ;
struct dcb_app_type {TYPE_1__ app; } ;
struct dcb_app {int dummy; } ;

/* Variables and functions */
 struct dcb_app_type* dcb_app_lookup (struct dcb_app*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dcb_lock ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

u8 dcb_getapp(struct net_device *dev, struct dcb_app *app)
{
	struct dcb_app_type *itr;
	u8 prio = 0;

	spin_lock_bh(&dcb_lock);
	itr = dcb_app_lookup(app, dev->ifindex, -1);
	if (itr)
		prio = itr->app.priority;
	spin_unlock_bh(&dcb_lock);

	return prio;
}