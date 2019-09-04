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
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct xmit_priv {int /*<<< orphan*/  free_xmit_extbuf_cnt; TYPE_1__ free_xmit_extbuf_queue; } ;
struct xmit_buf {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  s32 ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;

/* Variables and functions */
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _enter_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  get_list_head (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_list_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

s32 rtw_free_xmitbuf_ext(struct xmit_priv *pxmitpriv, struct xmit_buf *pxmitbuf)
{
	_irqL irqL;
	_queue *pfree_queue = &pxmitpriv->free_xmit_extbuf_queue;

_func_enter_;

	if(pxmitbuf==NULL)
	{
		return _FAIL;
	}

	_enter_critical(&pfree_queue->lock, &irqL);

	rtw_list_delete(&pxmitbuf->list);

	rtw_list_insert_tail(&(pxmitbuf->list), get_list_head(pfree_queue));
	pxmitpriv->free_xmit_extbuf_cnt++;
	#ifdef DBG_XMIT_BUF
	DBG_871X("DBG_XMIT_BUF FREE no=%d, free_xmit_extbuf_cnt=%d\n",pxmitbuf->no ,pxmitpriv->free_xmit_extbuf_cnt);
	#endif

	_exit_critical(&pfree_queue->lock, &irqL);

_func_exit_;

	return _SUCCESS;
}