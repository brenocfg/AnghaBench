#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct sas_task_slow {struct sas_task* task; } ;
struct sas_task {TYPE_1__* slow_task; int /*<<< orphan*/  task_state_flags; } ;
struct TYPE_2__ {int /*<<< orphan*/  completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAS_TASK_STATE_ABORTED ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 struct sas_task_slow* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct sas_task_slow* slow ; 
 int /*<<< orphan*/  timer ; 

__attribute__((used)) static void mvs_tmf_timedout(struct timer_list *t)
{
	struct sas_task_slow *slow = from_timer(slow, t, timer);
	struct sas_task *task = slow->task;

	task->task_state_flags |= SAS_TASK_STATE_ABORTED;
	complete(&task->slow_task->completion);
}