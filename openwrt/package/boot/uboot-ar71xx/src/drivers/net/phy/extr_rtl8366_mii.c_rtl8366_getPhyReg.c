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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */
 int RTL8366S_PHY_ACCESS_CTRL_REG ; 
 int /*<<< orphan*/  RTL8366S_PHY_ACCESS_DATA_REG ; 
 int RTL8366S_PHY_ADDR_MAX ; 
 int /*<<< orphan*/  RTL8366S_PHY_CTRL_READ ; 
 int RTL8366S_PHY_NO_MAX ; 
 int RTL8366S_PHY_NO_OFFSET ; 
 int RTL8366S_PHY_REG_MASK ; 
 int /*<<< orphan*/  printf (char*) ; 
 scalar_t__ rtl8366_readRegister (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ rtl8366_writeRegister (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rtl8366_getPhyReg(uint32_t phyNum, uint32_t reg, uint16_t *data)
{
    uint16_t phyAddr, regData;

    if (phyNum > RTL8366S_PHY_NO_MAX) {
		printf("rtl8366s: invalid phy number!\n");
		return -1;
	}

    if (phyNum > RTL8366S_PHY_ADDR_MAX) {
		printf("rtl8366s: invalid phy register number!\n");
		return -1;
	}

	if (rtl8366_writeRegister(RTL8366S_PHY_ACCESS_CTRL_REG,
                           RTL8366S_PHY_CTRL_READ))
        return -1;

    phyAddr = 0x8000 | (1 << (phyNum + RTL8366S_PHY_NO_OFFSET))
                     | (reg & RTL8366S_PHY_REG_MASK);
    if (rtl8366_writeRegister(phyAddr, 0))
        return -1;

    if (rtl8366_readRegister(RTL8366S_PHY_ACCESS_DATA_REG, &regData))
        return -1;

    if (data)
        *data = regData;

    return 0;
}