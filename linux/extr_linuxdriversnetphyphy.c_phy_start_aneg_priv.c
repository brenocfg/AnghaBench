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
struct phy_device {scalar_t__ autoneg; scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  link_timeout; scalar_t__ lp_advertising; int /*<<< orphan*/  drv; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_DISABLE ; 
 scalar_t__ AUTONEG_ENABLE ; 
 int EIO ; 
 scalar_t__ PHY_AN ; 
 int /*<<< orphan*/  PHY_AN_TIMEOUT ; 
 int /*<<< orphan*/  PHY_FORCE_TIMEOUT ; 
 scalar_t__ PHY_FORCING ; 
 scalar_t__ PHY_HALTED ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int phy_aneg_done (struct phy_device*) ; 
 int phy_config_aneg (struct phy_device*) ; 
 int /*<<< orphan*/  phy_polling_mode (struct phy_device*) ; 
 int /*<<< orphan*/  phy_sanitize_settings (struct phy_device*) ; 
 int /*<<< orphan*/  phy_trigger_machine (struct phy_device*,int) ; 

__attribute__((used)) static int phy_start_aneg_priv(struct phy_device *phydev, bool sync)
{
	bool trigger = 0;
	int err;

	if (!phydev->drv)
		return -EIO;

	mutex_lock(&phydev->lock);

	if (AUTONEG_DISABLE == phydev->autoneg)
		phy_sanitize_settings(phydev);

	/* Invalidate LP advertising flags */
	phydev->lp_advertising = 0;

	err = phy_config_aneg(phydev);
	if (err < 0)
		goto out_unlock;

	if (phydev->state != PHY_HALTED) {
		if (AUTONEG_ENABLE == phydev->autoneg) {
			phydev->state = PHY_AN;
			phydev->link_timeout = PHY_AN_TIMEOUT;
		} else {
			phydev->state = PHY_FORCING;
			phydev->link_timeout = PHY_FORCE_TIMEOUT;
		}
	}

	/* Re-schedule a PHY state machine to check PHY status because
	 * negotiation may already be done and aneg interrupt may not be
	 * generated.
	 */
	if (!phy_polling_mode(phydev) && phydev->state == PHY_AN) {
		err = phy_aneg_done(phydev);
		if (err > 0) {
			trigger = true;
			err = 0;
		}
	}

out_unlock:
	mutex_unlock(&phydev->lock);

	if (trigger)
		phy_trigger_machine(phydev, sync);

	return err;
}