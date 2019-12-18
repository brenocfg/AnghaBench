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
struct net_device {int /*<<< orphan*/  ifindex; TYPE_1__* dcbnl_ops; } ;
struct dcb_app_type {int /*<<< orphan*/  dcbx; int /*<<< orphan*/  app; int /*<<< orphan*/  ifindex; } ;
struct dcb_app {int /*<<< orphan*/  priority; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* getdcbx ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_APP_EVENT ; 
 int EEXIST ; 
 int /*<<< orphan*/  call_dcbevent_notifiers (int /*<<< orphan*/ ,struct dcb_app_type*) ; 
 int dcb_app_add (struct dcb_app*,int /*<<< orphan*/ ) ; 
 scalar_t__ dcb_app_lookup (struct dcb_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcb_lock ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dcb_app*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

int dcb_ieee_setapp(struct net_device *dev, struct dcb_app *new)
{
	struct dcb_app_type event;
	int err = 0;

	event.ifindex = dev->ifindex;
	memcpy(&event.app, new, sizeof(event.app));
	if (dev->dcbnl_ops->getdcbx)
		event.dcbx = dev->dcbnl_ops->getdcbx(dev);

	spin_lock_bh(&dcb_lock);
	/* Search for existing match and abort if found */
	if (dcb_app_lookup(new, dev->ifindex, new->priority)) {
		err = -EEXIST;
		goto out;
	}

	err = dcb_app_add(new, dev->ifindex);
out:
	spin_unlock_bh(&dcb_lock);
	if (!err)
		call_dcbevent_notifiers(DCB_APP_EVENT, &event);
	return err;
}