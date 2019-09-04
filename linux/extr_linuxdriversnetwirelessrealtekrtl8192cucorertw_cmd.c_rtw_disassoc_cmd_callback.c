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
struct mlme_priv {int /*<<< orphan*/  lock; } ;
struct cmd_obj {scalar_t__ res; } ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_3__ {struct mlme_priv mlmepriv; } ;
typedef  TYPE_1__ _adapter ;

/* Variables and functions */
 scalar_t__ H2C_SUCCESS ; 
 int /*<<< orphan*/  RT_TRACE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  _FW_LINKED ; 
 int /*<<< orphan*/  _drv_err_ ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _module_rtl871x_cmd_c_ ; 
 int /*<<< orphan*/  rtw_free_cmd_obj (struct cmd_obj*) ; 
 int /*<<< orphan*/  set_fwstate (struct mlme_priv*,int /*<<< orphan*/ ) ; 

void rtw_disassoc_cmd_callback(_adapter*	padapter,  struct cmd_obj *pcmd)
{
	_irqL	irqL;
	struct 	mlme_priv *pmlmepriv = &padapter->mlmepriv;
	
_func_enter_;	

	if (pcmd->res != H2C_SUCCESS)
	{
		_enter_critical_bh(&pmlmepriv->lock, &irqL);
		set_fwstate(pmlmepriv, _FW_LINKED);
		_exit_critical_bh(&pmlmepriv->lock, &irqL);
				
		RT_TRACE(_module_rtl871x_cmd_c_,_drv_err_,("\n ***Error: disconnect_cmd_callback Fail ***\n."));

		goto exit;
	}
#ifdef CONFIG_BR_EXT
	else //clear bridge database
		nat25_db_cleanup(padapter);
#endif //CONFIG_BR_EXT

	// free cmd
	rtw_free_cmd_obj(pcmd);
	
exit:
	
_func_exit_;	
}