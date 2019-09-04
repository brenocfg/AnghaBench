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
typedef  int u8 ;
typedef  int u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;
typedef  enum halmac_ret_status { ____Placeholder_halmac_ret_status } halmac_ret_status ;

/* Variables and functions */
 int BIT_MDIO_WFLAG_V1 ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_16 (struct halmac_adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 
 int HALMAC_RET_FAIL ; 
 int HALMAC_RET_SUCCESS ; 
 int HAL_INTF_PHY_PCIE_GEN1 ; 
 int HAL_INTF_PHY_PCIE_GEN2 ; 
 int /*<<< orphan*/  REG_MDIO_V1 ; 
 scalar_t__ REG_PCIE_MIX_CFG ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

enum halmac_ret_status
halmac_mdio_write_88xx(struct halmac_adapter *halmac_adapter, u8 addr, u16 data,
		       u8 speed)
{
	u8 tmp_u1b = 0;
	u32 count = 0;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;
	u8 real_addr = 0;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

	HALMAC_REG_WRITE_16(halmac_adapter, REG_MDIO_V1, data);

	/* address : 5bit */
	real_addr = (addr & 0x1F);
	HALMAC_REG_WRITE_8(halmac_adapter, REG_PCIE_MIX_CFG, real_addr);

	if (speed == HAL_INTF_PHY_PCIE_GEN1) {
		/* GEN1 page 0 */
		if (addr < 0x20) {
			/* select MDIO PHY Addr : reg 0x3F8[28:24]=5'b00 */
			HALMAC_REG_WRITE_8(halmac_adapter, REG_PCIE_MIX_CFG + 3,
					   0x00);

			/* GEN1 page 1 */
		} else {
			/* select MDIO PHY Addr : reg 0x3F8[28:24]=5'b01 */
			HALMAC_REG_WRITE_8(halmac_adapter, REG_PCIE_MIX_CFG + 3,
					   0x01);
		}

	} else if (speed == HAL_INTF_PHY_PCIE_GEN2) {
		/* GEN2 page 0 */
		if (addr < 0x20) {
			/* select MDIO PHY Addr : reg 0x3F8[28:24]=5'b10 */
			HALMAC_REG_WRITE_8(halmac_adapter, REG_PCIE_MIX_CFG + 3,
					   0x02);

			/* GEN2 page 1 */
		} else {
			/* select MDIO PHY Addr : reg 0x3F8[28:24]=5'b11 */
			HALMAC_REG_WRITE_8(halmac_adapter, REG_PCIE_MIX_CFG + 3,
					   0x03);
		}
	} else {
		pr_err("Error Speed !\n");
	}

	HALMAC_REG_WRITE_8(halmac_adapter, REG_PCIE_MIX_CFG,
			   HALMAC_REG_READ_8(halmac_adapter, REG_PCIE_MIX_CFG) |
				   BIT_MDIO_WFLAG_V1);

	tmp_u1b = HALMAC_REG_READ_8(halmac_adapter, REG_PCIE_MIX_CFG) &
		  BIT_MDIO_WFLAG_V1;
	count = 20;

	while (tmp_u1b && count != 0) {
		udelay(10);
		tmp_u1b = HALMAC_REG_READ_8(halmac_adapter, REG_PCIE_MIX_CFG) &
			  BIT_MDIO_WFLAG_V1;
		count--;
	}

	if (tmp_u1b) {
		pr_err("MDIO write fail!\n");
		return HALMAC_RET_FAIL;
	} else {
		return HALMAC_RET_SUCCESS;
	}
}