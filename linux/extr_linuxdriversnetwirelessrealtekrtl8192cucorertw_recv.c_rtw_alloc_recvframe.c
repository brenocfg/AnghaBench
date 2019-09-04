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
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;

/* Variables and functions */
 int /*<<< orphan*/  _enter_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical_bh (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 union recv_frame* _rtw_alloc_recvframe (TYPE_1__*) ; 

union recv_frame *rtw_alloc_recvframe (_queue *pfree_recv_queue)
{
	_irqL irqL;
	union recv_frame  *precvframe;
	
	_enter_critical_bh(&pfree_recv_queue->lock, &irqL);

	precvframe = _rtw_alloc_recvframe(pfree_recv_queue);

	_exit_critical_bh(&pfree_recv_queue->lock, &irqL);

	return precvframe;
}