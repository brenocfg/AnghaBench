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
typedef  int /*<<< orphan*/  PADAPTER ;
typedef  int HAL_INTF_PS_FUNC ;

/* Variables and functions */
 int /*<<< orphan*/  _TRUE ; 

__attribute__((used)) static u8 rtl8192cu_ps_func(PADAPTER Adapter,HAL_INTF_PS_FUNC efunc_id, u8 *val)
{	
	u8 bResult = _TRUE;
	switch(efunc_id){

		#if defined(CONFIG_AUTOSUSPEND) && defined(SUPPORT_HW_RFOFF_DETECTED)
		case HAL_USB_SELECT_SUSPEND:
			{
				u8 bfwpoll = *(( u8*)val);
				rtl8192c_set_FwSelectSuspend_cmd(Adapter,bfwpoll ,500);//note fw to support hw power down ping detect
			}
			break;
		#endif //CONFIG_AUTOSUSPEND && SUPPORT_HW_RFOFF_DETECTED

		default:
			break;
	}
	return bResult;
}