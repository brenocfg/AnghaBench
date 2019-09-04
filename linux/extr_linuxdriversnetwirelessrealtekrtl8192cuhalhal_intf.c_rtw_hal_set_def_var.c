#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_5__ {int /*<<< orphan*/  (* SetHalDefVarHandler ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_6__ {TYPE_1__ HalFunc; } ;
typedef  TYPE_2__ _adapter ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int /*<<< orphan*/  HAL_DEF_VARIABLE ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

u8 rtw_hal_set_def_var(_adapter *padapter, HAL_DEF_VARIABLE eVariable, PVOID pValue)
{	
	if(padapter->HalFunc.SetHalDefVarHandler)
		return padapter->HalFunc.SetHalDefVarHandler(padapter,eVariable,pValue);
	return _FAIL;
}