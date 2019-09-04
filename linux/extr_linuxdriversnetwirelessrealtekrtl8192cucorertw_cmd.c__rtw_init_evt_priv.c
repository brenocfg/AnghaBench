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
struct evt_priv {scalar_t__ evt_done_cnt; int /*<<< orphan*/  event_seq; } ;
typedef  int /*<<< orphan*/  sint ;

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_SET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 

sint _rtw_init_evt_priv(struct evt_priv *pevtpriv)
{
	sint res=_SUCCESS;

_func_enter_;	

#ifdef CONFIG_H2CLBK
	_rtw_init_sema(&(pevtpriv->lbkevt_done), 0);
	pevtpriv->lbkevt_limit = 0;
	pevtpriv->lbkevt_num = 0;
	pevtpriv->cmdevt_parm = NULL;		
#endif		
	
	//allocate DMA-able/Non-Page memory for cmd_buf and rsp_buf
	ATOMIC_SET(&pevtpriv->event_seq, 0);
	pevtpriv->evt_done_cnt = 0;

#ifdef CONFIG_EVENT_THREAD_MODE

	_rtw_init_sema(&(pevtpriv->evt_notify), 0);
	_rtw_init_sema(&(pevtpriv->terminate_evtthread_sema), 0);

	pevtpriv->evt_allocated_buf = rtw_zmalloc(MAX_EVTSZ + 4);	
	if (pevtpriv->evt_allocated_buf == NULL){
		res= _FAIL;
		goto exit;
		}
	pevtpriv->evt_buf = pevtpriv->evt_allocated_buf  +  4 - ((unsigned int)(pevtpriv->evt_allocated_buf) & 3);
	
		
#ifdef CONFIG_SDIO_HCI
	pevtpriv->allocated_c2h_mem = rtw_zmalloc(C2H_MEM_SZ +4); 
	
	if (pevtpriv->allocated_c2h_mem == NULL){
		res= _FAIL;
		goto exit;
	}

	pevtpriv->c2h_mem = pevtpriv->allocated_c2h_mem +  4\
	- ( (u32)(pevtpriv->allocated_c2h_mem) & 3);
#ifdef PLATFORM_OS_XP
	pevtpriv->pc2h_mdl= IoAllocateMdl((u8 *)pevtpriv->c2h_mem, C2H_MEM_SZ , FALSE, FALSE, NULL);
	
	if(pevtpriv->pc2h_mdl == NULL){
		res= _FAIL;
		goto exit;
	}
	MmBuildMdlForNonPagedPool(pevtpriv->pc2h_mdl);
#endif
#endif //end of CONFIG_SDIO_HCI

	_rtw_init_queue(&(pevtpriv->evt_queue));

exit:	

#endif //end of CONFIG_EVENT_THREAD_MODE

#ifdef CONFIG_C2H_WK
	_init_workitem(&pevtpriv->c2h_wk, c2h_wk_callback, NULL);
	pevtpriv->c2h_wk_alive = _FALSE;
	pevtpriv->c2h_queue = rtw_cbuf_alloc(C2H_QUEUE_MAX_LEN+1);
#endif

_func_exit_;		 

	return res;
}