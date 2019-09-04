#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  union recv_frame {int dummy; } recv_frame ;
typedef  int /*<<< orphan*/  sint ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;

/* Variables and functions */
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_enqueue_recvframe (union recv_frame*,TYPE_1__*) ; 

sint rtw_enqueue_recvframe(union recv_frame *precvframe, _queue *queue)
{
	sint ret;
	_irqL irqL;
	
	//_spinlock(&pfree_recv_queue->lock);
	_enter_critical_bh(&queue->lock, &irqL);
	ret = _rtw_enqueue_recvframe(precvframe, queue);
	//_rtw_spinunlock(&pfree_recv_queue->lock);
	_exit_critical_bh(&queue->lock, &irqL);

	return ret;
}