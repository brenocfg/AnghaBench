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
struct dcb_app_type {int /*<<< orphan*/  list; int /*<<< orphan*/  dcbx; int /*<<< orphan*/  app; int /*<<< orphan*/  ifindex; } ;
struct dcb_app {int /*<<< orphan*/  priority; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* getdcbx ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_APP_EVENT ; 
 int ENOENT ; 
 int /*<<< orphan*/  call_dcbevent_notifiers (int /*<<< orphan*/ ,struct dcb_app_type*) ; 
 struct dcb_app_type* dcb_app_lookup (struct dcb_app*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcb_lock ; 
 int /*<<< orphan*/  kfree (struct dcb_app_type*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct dcb_app*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

int dcb_ieee_delapp(struct net_device *dev, struct dcb_app *del)
{
	struct dcb_app_type *itr;
	struct dcb_app_type event;
	int err = -ENOENT;

	event.ifindex = dev->ifindex;
	memcpy(&event.app, del, sizeof(event.app));
	if (dev->dcbnl_ops->getdcbx)
		event.dcbx = dev->dcbnl_ops->getdcbx(dev);

	spin_lock_bh(&dcb_lock);
	/* Search for existing match and remove it. */
	if ((itr = dcb_app_lookup(del, dev->ifindex, del->priority))) {
		list_del(&itr->list);
		kfree(itr);
		err = 0;
	}

	spin_unlock_bh(&dcb_lock);
	if (!err)
		call_dcbevent_notifiers(DCB_APP_EVENT, &event);
	return err;
}