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
struct recv_buf {int /*<<< orphan*/  list; } ;
typedef  int /*<<< orphan*/  sint ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_1__ _queue ;
typedef  int /*<<< orphan*/  _irqL ;

/* Variables and functions */
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _enter_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _exit_critical (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_list_head (TYPE_1__*) ; 
 int /*<<< orphan*/  rtw_list_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

sint rtw_enqueue_recvbuf(struct recv_buf *precvbuf, _queue *queue)
{
	_irqL irqL;	

	_enter_critical(&queue->lock, &irqL);

	rtw_list_delete(&precvbuf->list);

	rtw_list_insert_tail(&precvbuf->list, get_list_head(queue));
	
	_exit_critical(&queue->lock, &irqL);


	return _SUCCESS;
	
}