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
typedef  scalar_t__ u8 ;
typedef  int /*<<< orphan*/  _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  HW_VAR_DM_FUNC_CLR ; 
 int /*<<< orphan*/  HW_VAR_DM_FUNC_SET ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

void Switch_DM_Func(_adapter *padapter, u8 mode, u8 enable)
{
#ifdef CONFIG_CONCURRENT_MODE	
	_adapter *pbuddy_adapter = padapter->pbuddy_adapter;
#endif

	if(enable == _TRUE)
	{
#ifdef CONFIG_CONCURRENT_MODE
		if(pbuddy_adapter)
		rtw_hal_set_hwreg(pbuddy_adapter, HW_VAR_DM_FUNC_SET, (u8 *)(&mode));
#endif
		rtw_hal_set_hwreg(padapter, HW_VAR_DM_FUNC_SET, (u8 *)(&mode));
	}
	else
	{
#ifdef CONFIG_CONCURRENT_MODE
		if(pbuddy_adapter)
		rtw_hal_set_hwreg(pbuddy_adapter, HW_VAR_DM_FUNC_CLR, (u8 *)(&mode));
#endif
		rtw_hal_set_hwreg(padapter, HW_VAR_DM_FUNC_CLR, (u8 *)(&mode));
	}

#if 0
	u8 val8;

	val8 = rtw_read8(padapter, FW_DYNAMIC_FUN_SWITCH);

	if(enable == _TRUE)
	{
		rtw_write8(padapter, FW_DYNAMIC_FUN_SWITCH, (val8 | mode));
	}
	else
	{
		rtw_write8(padapter, FW_DYNAMIC_FUN_SWITCH, (val8 & mode));
	}
#endif

}