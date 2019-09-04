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
struct adapter {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; int /*<<< orphan*/  mlmepriv; } ;
typedef  int sint ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _drv_info_ ; 
 int /*<<< orphan*/  _module_rtl871x_mlme_c_ ; 
 int check_fwstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

sint rtw_if_up(struct adapter *padapter)
{

	sint res;

	if (padapter->bDriverStopped || padapter->bSurpriseRemoved ||
		(check_fwstate(&padapter->mlmepriv, _FW_LINKED) == false)) {
		RT_TRACE(_module_rtl871x_mlme_c_, _drv_info_, ("rtw_if_up:bDriverStopped(%d) OR bSurpriseRemoved(%d)", padapter->bDriverStopped, padapter->bSurpriseRemoved));
		res = false;
	} else
		res =  true;
	return res;
}