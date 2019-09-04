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
typedef  int /*<<< orphan*/  u32 ;
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCM_CL45VEN_EEE_ADV ; 
 int /*<<< orphan*/  BRCM_CL45VEN_EEE_CONTROL ; 
 int LPI_FEATURE_EN ; 
 int LPI_FEATURE_EN_DIG1000X ; 
 int MDIO_EEE_1000T ; 
 int MDIO_EEE_100TX ; 
 int /*<<< orphan*/  MDIO_MMD_AN ; 
 int phy_read_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  phy_write_mmd (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int bcm_phy_set_eee(struct phy_device *phydev, bool enable)
{
	int val;

	/* Enable EEE at PHY level */
	val = phy_read_mmd(phydev, MDIO_MMD_AN, BRCM_CL45VEN_EEE_CONTROL);
	if (val < 0)
		return val;

	if (enable)
		val |= LPI_FEATURE_EN | LPI_FEATURE_EN_DIG1000X;
	else
		val &= ~(LPI_FEATURE_EN | LPI_FEATURE_EN_DIG1000X);

	phy_write_mmd(phydev, MDIO_MMD_AN, BRCM_CL45VEN_EEE_CONTROL, (u32)val);

	/* Advertise EEE */
	val = phy_read_mmd(phydev, MDIO_MMD_AN, BCM_CL45VEN_EEE_ADV);
	if (val < 0)
		return val;

	if (enable)
		val |= (MDIO_EEE_100TX | MDIO_EEE_1000T);
	else
		val &= ~(MDIO_EEE_100TX | MDIO_EEE_1000T);

	phy_write_mmd(phydev, MDIO_MMD_AN, BCM_CL45VEN_EEE_ADV, (u32)val);

	return 0;
}