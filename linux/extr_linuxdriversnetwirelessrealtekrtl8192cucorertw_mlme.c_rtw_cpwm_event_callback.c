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

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 

void rtw_cpwm_event_callback(PADAPTER padapter, u8 *pbuf)
{
#ifdef CONFIG_LPS_LCLK
	struct reportpwrstate_parm *preportpwrstate;
#endif

_func_enter_;

	RT_TRACE(_module_rtl871x_mlme_c_,_drv_err_,("rtw_cpwm_event_callback !!!\n"));
#ifdef CONFIG_LPS_LCLK
	preportpwrstate = (struct reportpwrstate_parm*)pbuf;
	preportpwrstate->state |= (u8)(padapter->pwrctrlpriv.cpwm_tog + 0x80);
	cpwm_int_hdl(padapter, preportpwrstate);
#endif

_func_exit_;

}