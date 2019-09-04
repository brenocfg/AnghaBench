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
struct mlme_priv {int /*<<< orphan*/  scan_to_timer; } ;
struct cmd_obj {scalar_t__ res; } ;
struct TYPE_3__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ H2C_DROPPED ; 
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtw_free_cmd_obj (struct cmd_obj*) ; 

void rtw_survey_cmd_callback(_adapter*	padapter ,  struct cmd_obj *pcmd)
{
	struct 	mlme_priv *pmlmepriv = &padapter->mlmepriv;

_func_enter_;

	if(pcmd->res == H2C_DROPPED)
	{
		//TODO: cancel timer and do timeout handler directly...
		//need to make timeout handlerOS independent
		_set_timer(&pmlmepriv->scan_to_timer, 1);
	}
	else if (pcmd->res != H2C_SUCCESS) {
		_set_timer(&pmlmepriv->scan_to_timer, 1);
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\n ********Error: MgntActrtw_set_802_11_bssid_LIST_SCAN Fail ************\n\n."));
	} 

	// free cmd
	rtw_free_cmd_obj(pcmd);

_func_exit_;	
}