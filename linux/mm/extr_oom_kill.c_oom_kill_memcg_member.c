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
struct task_struct {TYPE_1__* signal; } ;
struct TYPE_2__ {scalar_t__ oom_score_adj; } ;

/* Variables and functions */
 scalar_t__ OOM_SCORE_ADJ_MIN ; 
 int /*<<< orphan*/  __oom_kill_process (struct task_struct*,void*) ; 
 int /*<<< orphan*/  get_task_struct (struct task_struct*) ; 
 int /*<<< orphan*/  is_global_init (struct task_struct*) ; 

__attribute__((used)) static int oom_kill_memcg_member(struct task_struct *task, void *message)
{
	if (task->signal->oom_score_adj != OOM_SCORE_ADJ_MIN &&
	    !is_global_init(task)) {
		get_task_struct(task);
		__oom_kill_process(task, message);
	}
	return 0;
}