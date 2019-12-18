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
struct rq {int /*<<< orphan*/  sched_goidle; } ;

/* Variables and functions */
 int /*<<< orphan*/  schedstat_inc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_idle_core (struct rq*) ; 

__attribute__((used)) static void set_next_task_idle(struct rq *rq, struct task_struct *next)
{
	update_idle_core(rq);
	schedstat_inc(rq->sched_goidle);
}