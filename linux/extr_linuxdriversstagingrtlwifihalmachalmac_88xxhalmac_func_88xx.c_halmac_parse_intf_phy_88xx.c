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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct halmac_intf_phy_para_ {int cut; int plaform; int offset; int value; int ip_sel; } ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {int chip_version; scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;
typedef  enum halmac_intf_phy_platform { ____Placeholder_halmac_intf_phy_platform } halmac_intf_phy_platform ;
typedef  enum hal_intf_phy { ____Placeholder_hal_intf_phy } hal_intf_phy ;

/* Variables and functions */
#define  HALMAC_CHIP_VER_A_CUT 134 
#define  HALMAC_CHIP_VER_B_CUT 133 
#define  HALMAC_CHIP_VER_C_CUT 132 
#define  HALMAC_CHIP_VER_D_CUT 131 
#define  HALMAC_CHIP_VER_E_CUT 130 
#define  HALMAC_CHIP_VER_F_CUT 129 
#define  HALMAC_CHIP_VER_TEST 128 
 scalar_t__ HALMAC_INTF_PHY_CUT_A ; 
 scalar_t__ HALMAC_INTF_PHY_CUT_B ; 
 scalar_t__ HALMAC_INTF_PHY_CUT_C ; 
 scalar_t__ HALMAC_INTF_PHY_CUT_D ; 
 scalar_t__ HALMAC_INTF_PHY_CUT_E ; 
 scalar_t__ HALMAC_INTF_PHY_CUT_F ; 
 scalar_t__ HALMAC_INTF_PHY_CUT_TESTCHIP ; 
 int HALMAC_IP_SEL_INTF_PHY ; 
 int HALMAC_IP_SEL_MAC ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,int /*<<< orphan*/ ,scalar_t__) ; 
 int HALMAC_RET_FAIL ; 
 scalar_t__ HALMAC_RET_SUCCESS ; 
 int HAL_INTF_PHY_PCIE_GEN1 ; 
 int HAL_INTF_PHY_PCIE_GEN2 ; 
 int HAL_INTF_PHY_USB2 ; 
 int HAL_INTF_PHY_USB3 ; 
 scalar_t__ halmac_dbi_write8_88xx (struct halmac_adapter*,int,scalar_t__) ; 
 scalar_t__ halmac_mdio_write_88xx (struct halmac_adapter*,scalar_t__,int,int) ; 
 scalar_t__ halmac_usbphy_write_88xx (struct halmac_adapter*,scalar_t__,int,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

enum halmac_ret_status
halmac_parse_intf_phy_88xx(struct halmac_adapter *halmac_adapter,
			   struct halmac_intf_phy_para_ *intf_phy_para,
			   enum halmac_intf_phy_platform platform,
			   enum hal_intf_phy intf_phy)
{
	u16 value;
	u16 curr_cut;
	u16 offset;
	u16 ip_sel;
	struct halmac_intf_phy_para_ *curr_phy_para;
	struct halmac_api *halmac_api;
	void *driver_adapter = NULL;
	u8 result = HALMAC_RET_SUCCESS;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	switch (halmac_adapter->chip_version) {
	case HALMAC_CHIP_VER_A_CUT:
		curr_cut = (u16)HALMAC_INTF_PHY_CUT_A;
		break;
	case HALMAC_CHIP_VER_B_CUT:
		curr_cut = (u16)HALMAC_INTF_PHY_CUT_B;
		break;
	case HALMAC_CHIP_VER_C_CUT:
		curr_cut = (u16)HALMAC_INTF_PHY_CUT_C;
		break;
	case HALMAC_CHIP_VER_D_CUT:
		curr_cut = (u16)HALMAC_INTF_PHY_CUT_D;
		break;
	case HALMAC_CHIP_VER_E_CUT:
		curr_cut = (u16)HALMAC_INTF_PHY_CUT_E;
		break;
	case HALMAC_CHIP_VER_F_CUT:
		curr_cut = (u16)HALMAC_INTF_PHY_CUT_F;
		break;
	case HALMAC_CHIP_VER_TEST:
		curr_cut = (u16)HALMAC_INTF_PHY_CUT_TESTCHIP;
		break;
	default:
		return HALMAC_RET_FAIL;
	}

	for (curr_phy_para = intf_phy_para;; curr_phy_para++) {
		if (!(curr_phy_para->cut & curr_cut) ||
		    !(curr_phy_para->plaform & (u16)platform))
			continue;

		offset = curr_phy_para->offset;
		value = curr_phy_para->value;
		ip_sel = curr_phy_para->ip_sel;

		if (offset == 0xFFFF)
			break;

		if (ip_sel == HALMAC_IP_SEL_MAC) {
			HALMAC_REG_WRITE_8(halmac_adapter, (u32)offset,
					   (u8)value);
		} else if (intf_phy == HAL_INTF_PHY_USB2) {
			result = halmac_usbphy_write_88xx(halmac_adapter,
							  (u8)offset, value,
							  HAL_INTF_PHY_USB2);

			if (result != HALMAC_RET_SUCCESS)
				pr_err("[ERR]Write USB2PHY fail!\n");

		} else if (intf_phy == HAL_INTF_PHY_USB3) {
			result = halmac_usbphy_write_88xx(halmac_adapter,
							  (u8)offset, value,
							  HAL_INTF_PHY_USB3);

			if (result != HALMAC_RET_SUCCESS)
				pr_err("[ERR]Write USB3PHY fail!\n");

		} else if (intf_phy == HAL_INTF_PHY_PCIE_GEN1) {
			if (ip_sel == HALMAC_IP_SEL_INTF_PHY)
				result = halmac_mdio_write_88xx(
					halmac_adapter, (u8)offset, value,
					HAL_INTF_PHY_PCIE_GEN1);
			else
				result = halmac_dbi_write8_88xx(
					halmac_adapter, offset, (u8)value);

			if (result != HALMAC_RET_SUCCESS)
				pr_err("[ERR]MDIO write GEN1 fail!\n");

		} else if (intf_phy == HAL_INTF_PHY_PCIE_GEN2) {
			if (ip_sel == HALMAC_IP_SEL_INTF_PHY)
				result = halmac_mdio_write_88xx(
					halmac_adapter, (u8)offset, value,
					HAL_INTF_PHY_PCIE_GEN2);
			else
				result = halmac_dbi_write8_88xx(
					halmac_adapter, offset, (u8)value);

			if (result != HALMAC_RET_SUCCESS)
				pr_err("[ERR]MDIO write GEN2 fail!\n");
		} else {
			pr_err("[ERR]Parse intf phy cfg error!\n");
		}
	}

	return HALMAC_RET_SUCCESS;
}