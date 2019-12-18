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
struct percpu_lock {TYPE_1__* c; } ;
struct TYPE_2__ {int /*<<< orphan*/  v; } ;

/* Variables and functions */
 int rseq_cmpeqv_storev (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int rseq_cpu_start () ; 
 scalar_t__ rseq_likely (int) ; 
 int /*<<< orphan*/  rseq_smp_acquire__after_ctrl_dep () ; 

int rseq_this_cpu_lock(struct percpu_lock *lock)
{
	int cpu;

	for (;;) {
		int ret;

		cpu = rseq_cpu_start();
		ret = rseq_cmpeqv_storev(&lock->c[cpu].v,
					 0, 1, cpu);
		if (rseq_likely(!ret))
			break;
		/* Retry if comparison fails or rseq aborts. */
	}
	/*
	 * Acquire semantic when taking lock after control dependency.
	 * Matches rseq_smp_store_release().
	 */
	rseq_smp_acquire__after_ctrl_dep();
	return cpu;
}