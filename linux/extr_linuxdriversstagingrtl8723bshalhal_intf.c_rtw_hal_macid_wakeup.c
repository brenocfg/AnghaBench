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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int /*<<< orphan*/  HAL_DEF_MACID_SLEEP ; 
 int /*<<< orphan*/  HW_VAR_MACID_WAKEUP ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  rtw_hal_get_def_var (struct adapter*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  rtw_hal_set_hwreg (struct adapter*,int /*<<< orphan*/ ,int*) ; 

s32 rtw_hal_macid_wakeup(struct adapter *padapter, u32 macid)
{
	u8 support;


	support = false;
	rtw_hal_get_def_var(padapter, HAL_DEF_MACID_SLEEP, &support);
	if (false == support)
		return _FAIL;

	rtw_hal_set_hwreg(padapter, HW_VAR_MACID_WAKEUP, (u8 *)&macid);

	return _SUCCESS;
}