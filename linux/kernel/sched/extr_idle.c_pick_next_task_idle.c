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
struct rq {struct task_struct* idle; } ;

/* Variables and functions */
 int /*<<< orphan*/  put_prev_task (struct rq*,struct task_struct*) ; 
 int /*<<< orphan*/  set_next_task_idle (struct rq*,struct task_struct*) ; 

__attribute__((used)) static struct task_struct *
pick_next_task_idle(struct rq *rq, struct task_struct *prev, struct rq_flags *rf)
{
	struct task_struct *next = rq->idle;

	if (prev)
		put_prev_task(rq, prev);

	set_next_task_idle(rq, next);

	return next;
}