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
typedef  int u32 ;
struct cmd_priv {int /*<<< orphan*/  cmd_queue_sema; int /*<<< orphan*/  cmd_queue; int /*<<< orphan*/  padapter; } ;
struct cmd_obj {int /*<<< orphan*/  padapter; } ;
typedef  int /*<<< orphan*/  PADAPTER ;

/* Variables and functions */
 int _FAIL ; 
 int _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int _rtw_enqueue_cmd (int /*<<< orphan*/ *,struct cmd_obj*) ; 
 int /*<<< orphan*/  _rtw_up_sema (int /*<<< orphan*/ *) ; 
 int rtw_cmd_filter (struct cmd_priv*,struct cmd_obj*) ; 
 int /*<<< orphan*/  rtw_free_cmd_obj (struct cmd_obj*) ; 

u32 rtw_enqueue_cmd(struct cmd_priv *pcmdpriv, struct cmd_obj *cmd_obj)
{
	int res = _FAIL;
	PADAPTER padapter = pcmdpriv->padapter;
	
_func_enter_;	
	
	if (cmd_obj == NULL) {
		goto exit;
	}

	cmd_obj->padapter = padapter;

#ifdef CONFIG_CONCURRENT_MODE
	//change pcmdpriv to primary's pcmdpriv
	if (padapter->adapter_type != PRIMARY_ADAPTER && padapter->pbuddy_adapter)
		pcmdpriv = &(padapter->pbuddy_adapter->cmdpriv);
#endif	

	if( _FAIL == (res=rtw_cmd_filter(pcmdpriv, cmd_obj)) ) {
		rtw_free_cmd_obj(cmd_obj);
		goto exit;
	}

	res = _rtw_enqueue_cmd(&pcmdpriv->cmd_queue, cmd_obj);

	if(res == _SUCCESS)
		_rtw_up_sema(&pcmdpriv->cmd_queue_sema);
	
exit:	
	
_func_exit_;

	return res;
}