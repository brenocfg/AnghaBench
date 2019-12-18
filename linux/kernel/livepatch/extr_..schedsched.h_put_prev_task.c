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
struct task_struct {TYPE_1__* sched_class; } ;
struct rq {struct task_struct* curr; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* put_prev_task ) (struct rq*,struct task_struct*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  stub1 (struct rq*,struct task_struct*) ; 

__attribute__((used)) static inline void put_prev_task(struct rq *rq, struct task_struct *prev)
{
	WARN_ON_ONCE(rq->curr != prev);
	prev->sched_class->put_prev_task(rq, prev);
}