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
struct fcoe_fcf_device {struct fcoe_fcf* priv; scalar_t__ selected; int /*<<< orphan*/  fka_period; int /*<<< orphan*/  priority; int /*<<< orphan*/  mac; int /*<<< orphan*/  vfid; int /*<<< orphan*/  fc_map; int /*<<< orphan*/  switch_name; int /*<<< orphan*/  fabric_name; } ;
struct fcoe_fcf {int /*<<< orphan*/  list; struct fcoe_fcf_device* fcf_dev; int /*<<< orphan*/  fka_period; int /*<<< orphan*/  pri; int /*<<< orphan*/  fcf_mac; int /*<<< orphan*/  vfid; int /*<<< orphan*/  fc_map; int /*<<< orphan*/  switch_name; int /*<<< orphan*/  fabric_name; struct fcoe_ctlr* fip; } ;
struct fcoe_ctlr_device {int /*<<< orphan*/  lock; } ;
struct fcoe_ctlr {int /*<<< orphan*/  fcf_count; int /*<<< orphan*/  fcfs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (struct fcoe_fcf*) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  LIBFCOE_FIP_DBG (struct fcoe_ctlr*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fcoe_ctlr_device* fcoe_ctlr_to_ctlr_dev (struct fcoe_ctlr*) ; 
 struct fcoe_fcf_device* fcoe_fcf_device_add (struct fcoe_ctlr_device*,struct fcoe_fcf_device*) ; 
 int /*<<< orphan*/  kfree (struct fcoe_fcf_device*) ; 
 struct fcoe_fcf_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int fcoe_sysfs_fcf_add(struct fcoe_fcf *new)
{
	struct fcoe_ctlr *fip = new->fip;
	struct fcoe_ctlr_device *ctlr_dev;
	struct fcoe_fcf_device *temp, *fcf_dev;
	int rc = -ENOMEM;

	LIBFCOE_FIP_DBG(fip, "New FCF fab %16.16llx mac %pM\n",
			new->fabric_name, new->fcf_mac);

	temp = kzalloc(sizeof(*temp), GFP_KERNEL);
	if (!temp)
		goto out;

	temp->fabric_name = new->fabric_name;
	temp->switch_name = new->switch_name;
	temp->fc_map = new->fc_map;
	temp->vfid = new->vfid;
	memcpy(temp->mac, new->fcf_mac, ETH_ALEN);
	temp->priority = new->pri;
	temp->fka_period = new->fka_period;
	temp->selected = 0; /* default to unselected */

	/*
	 * If ctlr_dev doesn't exist then it means we're a libfcoe user
	 * who doesn't use fcoe_syfs and didn't allocate a fcoe_ctlr_device.
	 * fnic would be an example of a driver with this behavior. In this
	 * case we want to add the fcoe_fcf to the fcoe_ctlr list, but we
	 * don't want to make sysfs changes.
	 */

	ctlr_dev = fcoe_ctlr_to_ctlr_dev(fip);
	if (ctlr_dev) {
		mutex_lock(&ctlr_dev->lock);
		fcf_dev = fcoe_fcf_device_add(ctlr_dev, temp);
		if (unlikely(!fcf_dev)) {
			rc = -ENOMEM;
			mutex_unlock(&ctlr_dev->lock);
			goto out;
		}

		/*
		 * The fcoe_sysfs layer can return a CONNECTED fcf that
		 * has a priv (fcf was never deleted) or a CONNECTED fcf
		 * that doesn't have a priv (fcf was deleted). However,
		 * libfcoe will always delete FCFs before trying to add
		 * them. This is ensured because both recv_adv and
		 * age_fcfs are protected by the the fcoe_ctlr's mutex.
		 * This means that we should never get a FCF with a
		 * non-NULL priv pointer.
		 */
		BUG_ON(fcf_dev->priv);

		fcf_dev->priv = new;
		new->fcf_dev = fcf_dev;
		mutex_unlock(&ctlr_dev->lock);
	}

	list_add(&new->list, &fip->fcfs);
	fip->fcf_count++;
	rc = 0;

out:
	kfree(temp);
	return rc;
}