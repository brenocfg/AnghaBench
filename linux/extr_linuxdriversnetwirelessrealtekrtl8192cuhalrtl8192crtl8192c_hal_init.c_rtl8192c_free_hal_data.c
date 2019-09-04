#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ HalData; } ;
typedef  TYPE_1__ _adapter ;
typedef  int /*<<< orphan*/  HAL_DATA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG_8192C (char*) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rtw_mfree (scalar_t__,int) ; 

void rtl8192c_free_hal_data(_adapter * padapter)
{
_func_enter_;

	DBG_8192C("=====> rtl8192c_free_hal_data =====\n");

	if(padapter->HalData)
		rtw_mfree(padapter->HalData, sizeof(HAL_DATA_TYPE));
	DBG_8192C("<===== rtl8192c_free_hal_data =====\n");

_func_exit_;
}