#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int /*<<< orphan*/  (* SetHalDefVarHandler ) (struct adapter*,int,void*) ;} ;
struct adapter {TYPE_1__ HalFunc; } ;
typedef  enum HAL_DEF_VARIABLE { ____Placeholder_HAL_DEF_VARIABLE } HAL_DEF_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  stub1 (struct adapter*,int,void*) ; 

u8 rtw_hal_set_def_var(struct adapter *padapter, enum HAL_DEF_VARIABLE eVariable, void *pValue)
{
	if (padapter->HalFunc.SetHalDefVarHandler)
		return padapter->HalFunc.SetHalDefVarHandler(padapter, eVariable, pValue);
	return _FAIL;
}