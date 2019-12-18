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
struct smcd_dev {int /*<<< orphan*/  dev; int /*<<< orphan*/  event_wq; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLAN_VID_MASK ; 
 int /*<<< orphan*/  destroy_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smc_smcd_terminate (struct smcd_dev*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ smcd_dev_list ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void smcd_unregister_dev(struct smcd_dev *smcd)
{
	spin_lock(&smcd_dev_list.lock);
	list_del(&smcd->list);
	spin_unlock(&smcd_dev_list.lock);
	flush_workqueue(smcd->event_wq);
	destroy_workqueue(smcd->event_wq);
	smc_smcd_terminate(smcd, 0, VLAN_VID_MASK);

	device_del(&smcd->dev);
}