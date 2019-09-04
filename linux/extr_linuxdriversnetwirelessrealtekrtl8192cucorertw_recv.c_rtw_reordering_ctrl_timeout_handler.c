#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
struct recv_reorder_ctrl {int /*<<< orphan*/  reordering_ctrl_timer; TYPE_1__ pending_recvframe_queue; TYPE_2__* padapter; } ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;
struct TYPE_5__ {scalar_t__ bSurpriseRemoved; scalar_t__ bDriverStopped; } ;
typedef  TYPE_2__ _adapter ;

/* Variables and functions */
 int /*<<< orphan*/  REORDER_WAIT_TIME ; 
 scalar_t__ _TRUE ; 
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _set_timer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ recv_indicatepkts_in_order (TYPE_2__*,struct recv_reorder_ctrl*,scalar_t__) ; 

void rtw_reordering_ctrl_timeout_handler(void *pcontext)
{
	_irqL irql;
	struct recv_reorder_ctrl *preorder_ctrl = (struct recv_reorder_ctrl *)pcontext;
	_adapter *padapter = preorder_ctrl->padapter;
	_queue *ppending_recvframe_queue = &preorder_ctrl->pending_recvframe_queue;


	if(padapter->bDriverStopped ||padapter->bSurpriseRemoved)
	{
		return;
	}

	//DBG_871X("+rtw_reordering_ctrl_timeout_handler()=>\n");

	_enter_critical_bh(&ppending_recvframe_queue->lock, &irql);

	if(recv_indicatepkts_in_order(padapter, preorder_ctrl, _TRUE)==_TRUE)
	{
		_set_timer(&preorder_ctrl->reordering_ctrl_timer, REORDER_WAIT_TIME);		
	}

	_exit_critical_bh(&ppending_recvframe_queue->lock, &irql);

}