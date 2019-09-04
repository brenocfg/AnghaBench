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
typedef  scalar_t__ uint ;
struct TYPE_5__ {scalar_t__ (* hal_deinit ) (TYPE_2__*) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  hw_init_completed; TYPE_1__ HalFunc; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FALSE ; 
 scalar_t__ _SUCCESS ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_hal_init_c_ ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

uint rtw_hal_deinit(_adapter *padapter)
{
	uint	status = _SUCCESS;
	
_func_enter_;

	status = padapter->HalFunc.hal_deinit(padapter);

	if(status == _SUCCESS){
		padapter->hw_init_completed = _FALSE;
	}
	else
	{
		RT_TRACE(_module_hal_init_c_,_drv_err_,("\n rtw_hal_deinit: hal_init fail\n"));
	}
	
_func_exit_;
	
	return status;
}