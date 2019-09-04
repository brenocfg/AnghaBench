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
struct cmd_priv {int cmd_seq; scalar_t__ rsp_cnt; scalar_t__ cmd_done_cnt; scalar_t__ cmd_issued_cnt; int /*<<< orphan*/ * rsp_allocated_buf; int /*<<< orphan*/ * rsp_buf; int /*<<< orphan*/ * cmd_allocated_buf; int /*<<< orphan*/ * cmd_buf; int /*<<< orphan*/  cmd_queue; int /*<<< orphan*/  terminate_cmdthread_sema; int /*<<< orphan*/  cmd_queue_sema; } ;
typedef  int /*<<< orphan*/  sint ;
typedef  int SIZE_PTR ;

/* Variables and functions */
 int CMDBUFF_ALIGN_SZ ; 
 scalar_t__ MAX_CMDSZ ; 
 scalar_t__ MAX_RSPSZ ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_sema (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* rtw_zmalloc (scalar_t__) ; 

sint	_rtw_init_cmd_priv (struct	cmd_priv *pcmdpriv)
{
	sint res=_SUCCESS;
	
_func_enter_;	

	_rtw_init_sema(&(pcmdpriv->cmd_queue_sema), 0);
	//_rtw_init_sema(&(pcmdpriv->cmd_done_sema), 0);
	_rtw_init_sema(&(pcmdpriv->terminate_cmdthread_sema), 0);
	
	
	_rtw_init_queue(&(pcmdpriv->cmd_queue));
	
	//allocate DMA-able/Non-Page memory for cmd_buf and rsp_buf
	
	pcmdpriv->cmd_seq = 1;
	
	pcmdpriv->cmd_allocated_buf = rtw_zmalloc(MAX_CMDSZ + CMDBUFF_ALIGN_SZ);
	
	if (pcmdpriv->cmd_allocated_buf == NULL){
		res= _FAIL;
		goto exit;
	}
	
	pcmdpriv->cmd_buf = pcmdpriv->cmd_allocated_buf  +  CMDBUFF_ALIGN_SZ - ( (SIZE_PTR)(pcmdpriv->cmd_allocated_buf) & (CMDBUFF_ALIGN_SZ-1));
		
	pcmdpriv->rsp_allocated_buf = rtw_zmalloc(MAX_RSPSZ + 4);
	
	if (pcmdpriv->rsp_allocated_buf == NULL){
		res= _FAIL;
		goto exit;
	}
	
	pcmdpriv->rsp_buf = pcmdpriv->rsp_allocated_buf  +  4 - ( (SIZE_PTR)(pcmdpriv->rsp_allocated_buf) & 3);

	pcmdpriv->cmd_issued_cnt = pcmdpriv->cmd_done_cnt = pcmdpriv->rsp_cnt = 0;

exit:
	
_func_exit_;	  

	return res;
	
}