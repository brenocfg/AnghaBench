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
struct TYPE_2__ {int /*<<< orphan*/  exec_start; } ;
struct task_struct {TYPE_1__ se; } ;
struct rq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  rq_clock_task (struct rq*) ; 

__attribute__((used)) static void set_next_task_stop(struct rq *rq, struct task_struct *stop)
{
	stop->se.exec_start = rq_clock_task(rq);
}