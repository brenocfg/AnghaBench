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
struct phy_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MII_KSZ9031RN_FLP_BURST_TX_HI ; 
 int /*<<< orphan*/  MII_KSZ9031RN_FLP_BURST_TX_LO ; 
 int /*<<< orphan*/  OP_DATA ; 
 int genphy_restart_aneg (struct phy_device*) ; 
 int ksz9031_extended_write (struct phy_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int ksz9031_center_flp_timing(struct phy_device *phydev)
{
	int result;

	result = ksz9031_extended_write(phydev, OP_DATA, 0,
					MII_KSZ9031RN_FLP_BURST_TX_HI, 0x0006);
	if (result)
		return result;

	result = ksz9031_extended_write(phydev, OP_DATA, 0,
					MII_KSZ9031RN_FLP_BURST_TX_LO, 0x1A80);
	if (result)
		return result;

	return genphy_restart_aneg(phydev);
}