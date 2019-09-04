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
typedef  int u16 ;
struct halmac_api {int dummy; } ;
struct halmac_adapter {scalar_t__ halmac_api; void* driver_adapter; } ;

/* Variables and functions */
 int BIT_MDIO_RFLAG_V1 ; 
 int /*<<< orphan*/  DBG_DMESG ; 
 int /*<<< orphan*/  HALMAC_MSG_MDIO ; 
 int HALMAC_REG_READ_16 (struct halmac_adapter*,scalar_t__) ; 
 int HALMAC_REG_READ_8 (struct halmac_adapter*,scalar_t__) ; 
 int /*<<< orphan*/  HALMAC_REG_WRITE_8 (struct halmac_adapter*,scalar_t__,int) ; 
 int /*<<< orphan*/  HALMAC_RT_TRACE (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int HAL_INTF_PHY_PCIE_GEN1 ; 
 int HAL_INTF_PHY_PCIE_GEN2 ; 
 scalar_t__ REG_MDIO_V1 ; 
 scalar_t__ REG_PCIE_MIX_CFG ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  udelay (int) ; 

u16 halmac_mdio_read_88xx(struct halmac_adapter *halmac_adapter, u8 addr,
			  u8 speed

			  )
{
	u16 ret = 0;
	u8 tmp_u1b = 0;
	u32 count = 0;
	void *driver_adapter = NULL;
	struct halmac_api *halmac_api;
	u8 real_addr = 0;

	driver_adapter = halmac_adapter->driver_adapter;
	halmac_api = (struct halmac_api *)halmac_adapter->halmac_api;

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
				   BIT_MDIO_RFLAG_V1);

	tmp_u1b = HALMAC_REG_READ_8(halmac_adapter, REG_PCIE_MIX_CFG) &
		  BIT_MDIO_RFLAG_V1;
	count = 20;

	while (tmp_u1b && count != 0) {
		udelay(10);
		tmp_u1b = HALMAC_REG_READ_8(halmac_adapter, REG_PCIE_MIX_CFG) &
			  BIT_MDIO_RFLAG_V1;
		count--;
	}

	if (tmp_u1b) {
		ret = 0xFFFF;
		pr_err("MDIO read fail!\n");

	} else {
		ret = HALMAC_REG_READ_16(halmac_adapter, REG_MDIO_V1 + 2);
		HALMAC_RT_TRACE(driver_adapter, HALMAC_MSG_MDIO, DBG_DMESG,
				"Read Value = %x\n", ret);
	}

	return ret;
}