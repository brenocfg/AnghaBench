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
struct phy_device {int eee_broken_modes; } ;

/* Variables and functions */
 int /*<<< orphan*/  MDIO_AN_EEE_ADV ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int genphy_config_eee_advert(struct phy_device *phydev)
{
	int broken = phydev->eee_broken_modes;
	int old_adv, adv;

	/* Nothing to disable */
	if (!broken)
		return 0;

	/* If the following call fails, we assume that EEE is not
	 * supported by the phy. If we read 0, EEE is not advertised
	 * In both case, we don't need to continue
	 */
	adv = phy_read_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV);
	if (adv <= 0)
		return 0;

	old_adv = adv;
	adv &= ~broken;

	/* Advertising remains unchanged with the broken mask */
	if (old_adv == adv)
		return 0;

	phy_write_mmd(phydev, MDIO_MMD_AN, MDIO_AN_EEE_ADV, adv);

	return 1;
}