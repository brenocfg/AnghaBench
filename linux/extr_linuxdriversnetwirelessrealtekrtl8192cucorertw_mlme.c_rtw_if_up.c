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
typedef  scalar_t__ sint ;
struct TYPE_3__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; int /*<<< orphan*/  mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ _FALSE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 scalar_t__ check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

sint rtw_if_up(_adapter *padapter)	{

	sint res;
_func_enter_;		

	if( padapter->bDriverStopped || padapter->bSurpriseRemoved ||
		(check_fwstate(&padapter->mlmepriv, _FW_LINKED)== _FALSE)){		
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("rtw_if_up:bDriverStopped(%d) OR bSurpriseRemoved(%d)", padapter->bDriverStopped, padapter->bSurpriseRemoved));	
		res=_FALSE;
	}
	else
		res=  _TRUE;
	
_func_exit_;
	return res;
}