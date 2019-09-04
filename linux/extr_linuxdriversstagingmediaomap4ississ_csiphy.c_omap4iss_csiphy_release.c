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
struct iss_csiphy {int /*<<< orphan*/  mutex; scalar_t__ phy_in_use; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSI2_COMPLEXIO_CFG_PWD_CMD_OFF ; 
 int /*<<< orphan*/  csiphy_set_power (struct iss_csiphy*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void omap4iss_csiphy_release(struct iss_csiphy *phy)
{
	mutex_lock(&phy->mutex);
	if (phy->phy_in_use) {
		csiphy_set_power(phy, CSI2_COMPLEXIO_CFG_PWD_CMD_OFF);
		phy->phy_in_use = 0;
	}
	mutex_unlock(&phy->mutex);
}