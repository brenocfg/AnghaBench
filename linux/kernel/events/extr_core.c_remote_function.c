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
struct remote_function_call {int /*<<< orphan*/  info; int /*<<< orphan*/  (* func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  ret; struct task_struct* p; } ;

/* Variables and functions */
 int /*<<< orphan*/  ESRCH ; 
 struct task_struct* current ; 
 scalar_t__ smp_processor_id () ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 scalar_t__ task_cpu (struct task_struct*) ; 

__attribute__((used)) static void remote_function(void *data)
{
	struct remote_function_call *tfc = data;
	struct task_struct *p = tfc->p;

	if (p) {
		/* -EAGAIN */
		if (task_cpu(p) != smp_processor_id())
			return;

		/*
		 * Now that we're on right CPU with IRQs disabled, we can test
		 * if we hit the right task without races.
		 */

		tfc->ret = -ESRCH; /* No such (running) process */
		if (p != current)
			return;
	}

	tfc->ret = tfc->func(tfc->info);
}