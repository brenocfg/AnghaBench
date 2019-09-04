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
struct swait_queue_head {int dummy; } ;
struct swait_queue {int /*<<< orphan*/  task_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

void __finish_swait(struct swait_queue_head *q, struct swait_queue *wait)
{
	__set_current_state(TASK_RUNNING);
	if (!list_empty(&wait->task_list))
		list_del_init(&wait->task_list);
}