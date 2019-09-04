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
struct exynos5_usbdrd_phy {int extrefclk; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXYNOS5_DRD_PHYSS_LANE0_TX_DEBUG ; 
 int /*<<< orphan*/  EXYNOS5_DRD_PHYSS_LOSLEVEL_OVRD_IN ; 
 int /*<<< orphan*/  EXYNOS5_DRD_PHYSS_TX_VBOOSTLEVEL_OVRD_IN ; 
#define  EXYNOS5_FSEL_19MHZ2 131 
#define  EXYNOS5_FSEL_20MHZ 130 
#define  EXYNOS5_FSEL_24MHZ 129 
#define  EXYNOS5_FSEL_50MHZ 128 
 unsigned int LANE0_TX_DEBUG_RXDET_MEAS_TIME_19M2_20M ; 
 unsigned int LANE0_TX_DEBUG_RXDET_MEAS_TIME_24M ; 
 unsigned int LANE0_TX_DEBUG_RXDET_MEAS_TIME_48M_50M_52M ; 
 unsigned int LOSLEVEL_OVRD_IN_EN ; 
 unsigned int LOSLEVEL_OVRD_IN_LOS_BIAS_5420 ; 
 unsigned int LOSLEVEL_OVRD_IN_LOS_LEVEL_DEFAULT ; 
 unsigned int TX_VBOOSTLEVEL_OVRD_IN_VBOOST_5420 ; 
 int crport_ctrl_write (struct exynos5_usbdrd_phy*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int exynos5420_usbdrd_phy_calibrate(struct exynos5_usbdrd_phy *phy_drd)
{
	unsigned int temp;
	int ret = 0;

	/*
	 * Change los_bias to (0x5) for 28nm PHY from a
	 * default value (0x0); los_level is set as default
	 * (0x9) as also reflected in los_level[30:26] bits
	 * of PHYPARAM0 register.
	 */
	temp = LOSLEVEL_OVRD_IN_LOS_BIAS_5420 |
		LOSLEVEL_OVRD_IN_EN |
		LOSLEVEL_OVRD_IN_LOS_LEVEL_DEFAULT;
	ret = crport_ctrl_write(phy_drd,
				EXYNOS5_DRD_PHYSS_LOSLEVEL_OVRD_IN,
				temp);
	if (ret) {
		dev_err(phy_drd->dev,
			"Failed setting Loss-of-Signal level for SuperSpeed\n");
		return ret;
	}

	/*
	 * Set tx_vboost_lvl to (0x5) for 28nm PHY Tuning,
	 * to raise Tx signal level from its default value of (0x4)
	 */
	temp = TX_VBOOSTLEVEL_OVRD_IN_VBOOST_5420;
	ret = crport_ctrl_write(phy_drd,
				EXYNOS5_DRD_PHYSS_TX_VBOOSTLEVEL_OVRD_IN,
				temp);
	if (ret) {
		dev_err(phy_drd->dev,
			"Failed setting Tx-Vboost-Level for SuperSpeed\n");
		return ret;
	}

	/*
	 * Set proper time to wait for RxDetect measurement, for
	 * desired reference clock of PHY, by tuning the CR_PORT
	 * register LANE0.TX_DEBUG which is internal to PHY.
	 * This fixes issue with few USB 3.0 devices, which are
	 * not detected (not even generate interrupts on the bus
	 * on insertion) without this change.
	 * e.g. Samsung SUM-TSB16S 3.0 USB drive.
	 */
	switch (phy_drd->extrefclk) {
	case EXYNOS5_FSEL_50MHZ:
		temp = LANE0_TX_DEBUG_RXDET_MEAS_TIME_48M_50M_52M;
		break;
	case EXYNOS5_FSEL_20MHZ:
	case EXYNOS5_FSEL_19MHZ2:
		temp = LANE0_TX_DEBUG_RXDET_MEAS_TIME_19M2_20M;
		break;
	case EXYNOS5_FSEL_24MHZ:
	default:
		temp = LANE0_TX_DEBUG_RXDET_MEAS_TIME_24M;
		break;
	}

	ret = crport_ctrl_write(phy_drd,
				EXYNOS5_DRD_PHYSS_LANE0_TX_DEBUG,
				temp);
	if (ret)
		dev_err(phy_drd->dev,
			"Fail to set RxDet measurement time for SuperSpeed\n");

	return ret;
}