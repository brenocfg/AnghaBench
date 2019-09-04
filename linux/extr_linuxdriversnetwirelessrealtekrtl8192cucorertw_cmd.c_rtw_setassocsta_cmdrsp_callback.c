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
struct sta_priv {int dummy; } ;
struct sta_info {int /*<<< orphan*/  mac_id; int /*<<< orphan*/  aid; } ;
struct set_assocsta_rsp {int /*<<< orphan*/  cam_id; } ;
struct set_assocsta_parm {int /*<<< orphan*/  addr; } ;
struct mlme_priv {int /*<<< orphan*/  lock; } ;
struct cmd_obj {scalar_t__ rsp; scalar_t__ parmbuf; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_3__ {struct mlme_priv mlmepriv; struct sta_priv stapriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WIFI_MP_STATE ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _FW_UNDER_LINKING ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _clr_fwstate_ (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 scalar_t__ check_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtw_free_cmd_obj (struct cmd_obj*) ; 
 struct sta_info* rtw_get_stainfo (struct sta_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

void rtw_setassocsta_cmdrsp_callback(_adapter*	padapter,  struct cmd_obj *pcmd)
{
	_irqL	irqL;
	struct sta_priv * pstapriv = &padapter->stapriv;
	struct mlme_priv	*pmlmepriv = &padapter->mlmepriv;	
	struct set_assocsta_parm* passocsta_parm = (struct set_assocsta_parm*)(pcmd->parmbuf);
	struct set_assocsta_rsp* passocsta_rsp = (struct set_assocsta_rsp*) (pcmd->rsp);		
	struct sta_info*	psta = rtw_get_stainfo(pstapriv, passocsta_parm->addr);

_func_enter_;	
	
	if(psta==NULL)
	{
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\nERROR: setassocsta_cmdrsp_callbac => can't get sta_info \n\n"));
		goto exit;
	}
	
	psta->aid = psta->mac_id = passocsta_rsp->cam_id;

	_enter_critical_bh(&pmlmepriv->lock, &irqL);

	if ((check_fwstate(pmlmepriv, WIFI_MP_STATE) == _TRUE) && (check_fwstate(pmlmepriv, _FW_UNDER_LINKING) == _TRUE))           	
		_clr_fwstate_(pmlmepriv, _FW_UNDER_LINKING);

       set_fwstate(pmlmepriv, _FW_LINKED);       	   
	_exit_critical_bh(&pmlmepriv->lock, &irqL);

exit:	  
	rtw_free_cmd_obj(pcmd);

_func_exit_;	  
}