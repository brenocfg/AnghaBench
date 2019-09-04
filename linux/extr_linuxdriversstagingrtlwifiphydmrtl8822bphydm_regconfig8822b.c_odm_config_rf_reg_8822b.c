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
struct phy_dm_struct {int dummy; } ;
typedef  enum odm_rf_radio_path { ____Placeholder_odm_rf_radio_path } odm_rf_radio_path ;

/* Variables and functions */
 int /*<<< orphan*/  ODM_delay_us (int) ; 
 int /*<<< orphan*/  ODM_sleep_ms (int) ; 
 int /*<<< orphan*/  RFREGOFFSETMASK ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int,int,int /*<<< orphan*/ ,int) ; 

void odm_config_rf_reg_8822b(struct phy_dm_struct *dm, u32 addr, u32 data,
			     enum odm_rf_radio_path RF_PATH, u32 reg_addr)
{
	if (addr == 0xffe) {
		ODM_sleep_ms(50);
	} else if (addr == 0xfe) {
		ODM_delay_us(100);
	} else {
		odm_set_rf_reg(dm, RF_PATH, reg_addr, RFREGOFFSETMASK, data);

		/* Add 1us delay between BB/RF register setting. */
		ODM_delay_us(1);
	}
}