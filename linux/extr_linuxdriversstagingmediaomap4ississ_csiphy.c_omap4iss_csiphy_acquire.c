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
struct iss_csiphy {int phy_in_use; int /*<<< orphan*/  mutex; int /*<<< orphan*/  csi2; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_COMPLEXIO_CFG_PWD_CMD_ON ; 
 int /*<<< orphan*/  csiphy_dphy_config (struct iss_csiphy*) ; 
 int /*<<< orphan*/  csiphy_lanes_config (struct iss_csiphy*) ; 
 int csiphy_set_power (struct iss_csiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int omap4iss_csi2_reset (int /*<<< orphan*/ ) ; 

int omap4iss_csiphy_acquire(struct iss_csiphy *phy)
{
	int rval;

	mutex_lock(&phy->mutex);

	rval = omap4iss_csi2_reset(phy->csi2);
	if (rval)
		goto done;

	csiphy_dphy_config(phy);
	csiphy_lanes_config(phy);

	rval = csiphy_set_power(phy, CSI2_COMPLEXIO_CFG_PWD_CMD_ON);
	if (rval)
		goto done;

	phy->phy_in_use = 1;

done:
	mutex_unlock(&phy->mutex);
	return rval;
}