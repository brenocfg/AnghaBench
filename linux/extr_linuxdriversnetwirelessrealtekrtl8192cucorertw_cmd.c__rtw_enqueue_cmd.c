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
struct cmd_obj {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  sint ;
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _enter_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

sint	_rtw_enqueue_cmd(_queue *queue, struct cmd_obj *obj)
{
	_irqL irqL;

_func_enter_;

	if (obj == NULL)
		goto exit;

	//_enter_critical_bh(&queue->lock, &irqL);
	_enter_critical(&queue->lock, &irqL);	

	rtw_list_insert_tail(&obj->list, &queue->queue);

	//_exit_critical_bh(&queue->lock, &irqL);	
	_exit_critical(&queue->lock, &irqL);

exit:	

_func_exit_;

	return _SUCCESS;
}