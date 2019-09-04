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
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BIT0 ; 
 int /*<<< orphan*/  DBG_871X_SEL_NL (void*,char*,char,...) ; 
 int /*<<< orphan*/  HW_VAR_DM_FLAG ; 
 int RTW_ODM_ABILITY_MAX ; 
 scalar_t__* odm_ability_str ; 
 int /*<<< orphan*/  rtw_hal_get_hwreg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void rtw_odm_ability_msg(void *sel, struct adapter *adapter)
{
	u32 ability = 0;
	int i;

	rtw_hal_get_hwreg(adapter, HW_VAR_DM_FLAG, (u8 *)&ability);
	DBG_871X_SEL_NL(sel, "odm.SupportAbility = 0x%08x\n", ability);
	for (i = 0; i < RTW_ODM_ABILITY_MAX; i++) {
		if (odm_ability_str[i])
			DBG_871X_SEL_NL(sel, "%cBIT%-2d %s\n",
					(BIT0 << i) & ability ? '+' : ' ', i,
					odm_ability_str[i]);
	}
}