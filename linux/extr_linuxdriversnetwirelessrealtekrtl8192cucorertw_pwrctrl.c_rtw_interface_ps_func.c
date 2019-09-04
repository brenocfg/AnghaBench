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
typedef  int /*<<< orphan*/  _adapter ;
typedef  int /*<<< orphan*/  HAL_INTF_PS_FUNC ;

/* Variables and functions */
 int /*<<< orphan*/  _TRUE ; 
 int /*<<< orphan*/  rtw_hal_intf_ps_func (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

u8 rtw_interface_ps_func(_adapter *padapter,HAL_INTF_PS_FUNC efunc_id,u8* val)
{
	u8 bResult = _TRUE;

	rtw_hal_intf_ps_func(padapter,efunc_id,val);

	return bResult;
}