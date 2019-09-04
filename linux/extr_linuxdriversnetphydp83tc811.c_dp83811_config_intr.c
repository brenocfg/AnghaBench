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
struct phy_device {scalar_t__ interrupts; } ;

/* Variables and functions */
 int DP83811_ANEG_COMPLETE_INT_EN ; 
 int DP83811_ENERGY_DET_INT_EN ; 
 int DP83811_ESD_EVENT_INT_EN ; 
 int DP83811_JABBER_DET_INT_EN ; 
 int DP83811_LINK_QUAL_INT_EN ; 
 int DP83811_LINK_STAT_INT_EN ; 
 int DP83811_LPS_INT_EN ; 
 int DP83811_MS_TRAINING_INT_EN ; 
 int DP83811_NO_FRAME_INT_EN ; 
 int DP83811_OVERTEMP_INT_EN ; 
 int DP83811_OVERVOLTAGE_INT_EN ; 
 int DP83811_POLARITY_INT_EN ; 
 int DP83811_POR_DONE_INT_EN ; 
 int DP83811_RX_ERR_HF_INT_EN ; 
 int DP83811_SLEEP_MODE_INT_EN ; 
 int DP83811_UNDERVOLTAGE_INT_EN ; 
 int DP83811_WOL_INT_EN ; 
 int /*<<< orphan*/  MII_DP83811_INT_STAT1 ; 
 int /*<<< orphan*/  MII_DP83811_INT_STAT2 ; 
 int /*<<< orphan*/  MII_DP83811_INT_STAT3 ; 
 scalar_t__ PHY_INTERRUPT_ENABLED ; 
 int phy_read (struct phy_device*,int /*<<< orphan*/ ) ; 
 int phy_write (struct phy_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dp83811_config_intr(struct phy_device *phydev)
{
	int misr_status, err;

	if (phydev->interrupts == PHY_INTERRUPT_ENABLED) {
		misr_status = phy_read(phydev, MII_DP83811_INT_STAT1);
		if (misr_status < 0)
			return misr_status;

		misr_status |= (DP83811_RX_ERR_HF_INT_EN |
				DP83811_MS_TRAINING_INT_EN |
				DP83811_ANEG_COMPLETE_INT_EN |
				DP83811_ESD_EVENT_INT_EN |
				DP83811_WOL_INT_EN |
				DP83811_LINK_STAT_INT_EN |
				DP83811_ENERGY_DET_INT_EN |
				DP83811_LINK_QUAL_INT_EN);

		err = phy_write(phydev, MII_DP83811_INT_STAT1, misr_status);
		if (err < 0)
			return err;

		misr_status = phy_read(phydev, MII_DP83811_INT_STAT2);
		if (misr_status < 0)
			return misr_status;

		misr_status |= (DP83811_JABBER_DET_INT_EN |
				DP83811_POLARITY_INT_EN |
				DP83811_SLEEP_MODE_INT_EN |
				DP83811_OVERTEMP_INT_EN |
				DP83811_OVERVOLTAGE_INT_EN |
				DP83811_UNDERVOLTAGE_INT_EN);

		err = phy_write(phydev, MII_DP83811_INT_STAT2, misr_status);
		if (err < 0)
			return err;

		misr_status = phy_read(phydev, MII_DP83811_INT_STAT3);
		if (misr_status < 0)
			return misr_status;

		misr_status |= (DP83811_LPS_INT_EN |
				DP83811_NO_FRAME_INT_EN |
				DP83811_POR_DONE_INT_EN);

		err = phy_write(phydev, MII_DP83811_INT_STAT3, misr_status);

	} else {
		err = phy_write(phydev, MII_DP83811_INT_STAT1, 0);
		if (err < 0)
			return err;

		err = phy_write(phydev, MII_DP83811_INT_STAT2, 0);
		if (err < 0)
			return err;

		err = phy_write(phydev, MII_DP83811_INT_STAT3, 0);
	}

	return err;
}