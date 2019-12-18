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
typedef  int u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AR91XX_ETH0_PLL_SHIFT ; 
 int /*<<< orphan*/  AR91XX_PLL_REG_ETH0_INT_CLOCK ; 
 int /*<<< orphan*/  AR91XX_PLL_REG_ETH_CONFIG ; 
 int /*<<< orphan*/  BUG () ; 
#define  SPEED_10 130 
#define  SPEED_100 129 
#define  SPEED_1000 128 
 int /*<<< orphan*/  ar71xx_set_pll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar91xx_set_pll_ge0(int speed)
{
	//u32 val = ar71xx_get_eth_pll(0, speed);
	u32 pll_val;

	switch (speed) {
	case SPEED_10:
		pll_val = 0x00441099;
		break;
	case SPEED_100:
		pll_val = 0x13000a44;
		break;
	case SPEED_1000:
		pll_val = 0x1a000000;
		break;
	default:
		BUG();
	}

	ar71xx_set_pll(AR91XX_PLL_REG_ETH_CONFIG, AR91XX_PLL_REG_ETH0_INT_CLOCK,
			 pll_val, AR91XX_ETH0_PLL_SHIFT);
}