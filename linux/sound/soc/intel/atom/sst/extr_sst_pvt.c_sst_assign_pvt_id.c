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
struct intel_sst_drv {int /*<<< orphan*/  block_lock; int /*<<< orphan*/  pvt_id; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int SST_MAX_BLOCKS ; 
 int /*<<< orphan*/  change_bit (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int ffz (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int sst_assign_pvt_id(struct intel_sst_drv *drv)
{
	int local;

	spin_lock(&drv->block_lock);
	/* find first zero index from lsb */
	local = ffz(drv->pvt_id);
	dev_dbg(drv->dev, "pvt_id assigned --> %d\n", local);
	if (local >= SST_MAX_BLOCKS){
		spin_unlock(&drv->block_lock);
		dev_err(drv->dev, "PVT _ID error: no free id blocks ");
		return -EINVAL;
	}
	/* toggle the index */
	change_bit(local, &drv->pvt_id);
	spin_unlock(&drv->block_lock);
	return local;
}