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

/* Variables and functions */
 int /*<<< orphan*/  AR71XX_MII_REG_MII0_CTRL ; 
 int /*<<< orphan*/  AR913X_ETH0_PLL_SHIFT ; 
 int /*<<< orphan*/  AR913X_PLL_REG_ETH0_INT_CLOCK ; 
 int /*<<< orphan*/  AR913X_PLL_REG_ETH_CONFIG ; 
 int /*<<< orphan*/  ath79_get_eth_pll (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath79_mii_ctrl_set_speed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ath79_set_pll (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ar91xx_set_speed_ge0(int speed)
{
	u32 val = ath79_get_eth_pll(0, speed);

	ath79_set_pll(AR913X_PLL_REG_ETH_CONFIG, AR913X_PLL_REG_ETH0_INT_CLOCK,
			 val, AR913X_ETH0_PLL_SHIFT);
	ath79_mii_ctrl_set_speed(AR71XX_MII_REG_MII0_CTRL, speed);
}