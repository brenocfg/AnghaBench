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

/* Variables and functions */
 int /*<<< orphan*/  ODM_RF_PATH_A ; 
 int /*<<< orphan*/  ODM_delay_ms (int) ; 
 int RFREGOFFSETMASK ; 
 int /*<<< orphan*/  RF_CHNLBW ; 
 int odm_get_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  odm_set_rf_reg (struct phy_dm_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void _phy_lc_calibrate_8822b(struct phy_dm_struct *dm)
{
	u32 lc_cal = 0, cnt = 0;

	/*backup RF0x18*/
	lc_cal = odm_get_rf_reg(dm, ODM_RF_PATH_A, RF_CHNLBW, RFREGOFFSETMASK);

	/*Start LCK*/
	odm_set_rf_reg(dm, ODM_RF_PATH_A, RF_CHNLBW, RFREGOFFSETMASK,
		       lc_cal | 0x08000);

	ODM_delay_ms(100);

	for (cnt = 0; cnt < 100; cnt++) {
		if (odm_get_rf_reg(dm, ODM_RF_PATH_A, RF_CHNLBW, 0x8000) != 0x1)
			break;
		ODM_delay_ms(10);
	}

	/*Recover channel number*/
	odm_set_rf_reg(dm, ODM_RF_PATH_A, RF_CHNLBW, RFREGOFFSETMASK, lc_cal);
}