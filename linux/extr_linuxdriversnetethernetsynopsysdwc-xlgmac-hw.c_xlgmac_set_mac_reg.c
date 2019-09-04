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
typedef  int /*<<< orphan*/  u8 ;
struct xlgmac_pdata {scalar_t__ mac_regs; int /*<<< orphan*/  netdev; } ;
struct netdev_hw_addr {int /*<<< orphan*/ * addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAC_MACA1HR_AE_LEN ; 
 int /*<<< orphan*/  MAC_MACA1HR_AE_POS ; 
 scalar_t__ MAC_MACA_INC ; 
 unsigned int XLGMAC_SET_REG_BITS (unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  drv ; 
 int /*<<< orphan*/  netif_dbg (struct xlgmac_pdata*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  writel (unsigned int,scalar_t__) ; 

__attribute__((used)) static void xlgmac_set_mac_reg(struct xlgmac_pdata *pdata,
			       struct netdev_hw_addr *ha,
			       unsigned int *mac_reg)
{
	unsigned int mac_addr_hi, mac_addr_lo;
	u8 *mac_addr;

	mac_addr_lo = 0;
	mac_addr_hi = 0;

	if (ha) {
		mac_addr = (u8 *)&mac_addr_lo;
		mac_addr[0] = ha->addr[0];
		mac_addr[1] = ha->addr[1];
		mac_addr[2] = ha->addr[2];
		mac_addr[3] = ha->addr[3];
		mac_addr = (u8 *)&mac_addr_hi;
		mac_addr[0] = ha->addr[4];
		mac_addr[1] = ha->addr[5];

		netif_dbg(pdata, drv, pdata->netdev,
			  "adding mac address %pM at %#x\n",
			  ha->addr, *mac_reg);

		mac_addr_hi = XLGMAC_SET_REG_BITS(mac_addr_hi,
						  MAC_MACA1HR_AE_POS,
						MAC_MACA1HR_AE_LEN,
						1);
	}

	writel(mac_addr_hi, pdata->mac_regs + *mac_reg);
	*mac_reg += MAC_MACA_INC;
	writel(mac_addr_lo, pdata->mac_regs + *mac_reg);
	*mac_reg += MAC_MACA_INC;
}