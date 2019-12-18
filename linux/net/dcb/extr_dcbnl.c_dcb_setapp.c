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
struct net_device {int /*<<< orphan*/  ifindex; TYPE_1__* dcbnl_ops; } ;
struct TYPE_4__ {scalar_t__ priority; } ;
struct dcb_app_type {int /*<<< orphan*/  list; TYPE_2__ app; int /*<<< orphan*/  dcbx; int /*<<< orphan*/  ifindex; } ;
struct dcb_app {scalar_t__ priority; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* getdcbx ) (struct net_device*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DCB_APP_EVENT ; 
 int /*<<< orphan*/  call_dcbevent_notifiers (int /*<<< orphan*/ ,struct dcb_app_type*) ; 
 int dcb_app_add (struct dcb_app*,int /*<<< orphan*/ ) ; 
 struct dcb_app_type* dcb_app_lookup (struct dcb_app*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dcb_lock ; 
 int /*<<< orphan*/  kfree (struct dcb_app_type*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,struct dcb_app*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct net_device*) ; 

int dcb_setapp(struct net_device *dev, struct dcb_app *new)
{
	struct dcb_app_type *itr;
	struct dcb_app_type event;
	int err = 0;

	event.ifindex = dev->ifindex;
	memcpy(&event.app, new, sizeof(event.app));
	if (dev->dcbnl_ops->getdcbx)
		event.dcbx = dev->dcbnl_ops->getdcbx(dev);

	spin_lock_bh(&dcb_lock);
	/* Search for existing match and replace */
	itr = dcb_app_lookup(new, dev->ifindex, -1);
	if (itr) {
		if (new->priority)
			itr->app.priority = new->priority;
		else {
			list_del(&itr->list);
			kfree(itr);
		}
		goto out;
	}
	/* App type does not exist add new application type */
	if (new->priority)
		err = dcb_app_add(new, dev->ifindex);
out:
	spin_unlock_bh(&dcb_lock);
	if (!err)
		call_dcbevent_notifiers(DCB_APP_EVENT, &event);
	return err;
}