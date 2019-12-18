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
struct task_struct {int dummy; } ;
struct rq_flags {int dummy; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 struct task_struct* _pick_next_task_rt (struct rq*) ; 
 int /*<<< orphan*/  sched_rt_runnable (struct rq*) ; 
 int /*<<< orphan*/  set_next_task_rt (struct rq*,struct task_struct*) ; 

__attribute__((used)) static struct task_struct *
pick_next_task_rt(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	struct task_struct *p;

	WARN_ON_ONCE(prev || rf);

	if (!sched_rt_runnable(rq))
		return NULL;

	p = _pick_next_task_rt(rq);
	set_next_task_rt(rq, p);
	return p;
}