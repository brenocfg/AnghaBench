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
struct ag71xx_platform_data {int reset_bit; scalar_t__ is_ar724x; } ;
struct ag71xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AG71XX_REG_MAC_CFG1 ; 
 int AR71XX_RESET_GE0_PHY ; 
 int AR71XX_RESET_GE1_PHY ; 
 int /*<<< orphan*/  MAC_CFG1_SR ; 
 int /*<<< orphan*/  ag71xx_dma_reset (struct ag71xx*) ; 
 struct ag71xx_platform_data* ag71xx_get_pdata (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_setup (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_hw_stop (struct ag71xx*) ; 
 int /*<<< orphan*/  ag71xx_sb (struct ag71xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath79_device_reset_clear (int) ; 
 int /*<<< orphan*/  ath79_device_reset_set (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void ag71xx_hw_init(struct ag71xx *ag)
{
	struct ag71xx_platform_data *pdata = ag71xx_get_pdata(ag);
	u32 reset_mask = pdata->reset_bit;

	ag71xx_hw_stop(ag);

	if (pdata->is_ar724x) {
		u32 reset_phy = reset_mask;

		reset_phy &= AR71XX_RESET_GE0_PHY | AR71XX_RESET_GE1_PHY;
		reset_mask &= ~(AR71XX_RESET_GE0_PHY | AR71XX_RESET_GE1_PHY);

		ath79_device_reset_set(reset_phy);
		msleep(50);
		ath79_device_reset_clear(reset_phy);
		msleep(200);
	}

	ag71xx_sb(ag, AG71XX_REG_MAC_CFG1, MAC_CFG1_SR);
	udelay(20);

	ath79_device_reset_set(reset_mask);
	msleep(100);
	ath79_device_reset_clear(reset_mask);
	msleep(200);

	ag71xx_hw_setup(ag);

	ag71xx_dma_reset(ag);
}