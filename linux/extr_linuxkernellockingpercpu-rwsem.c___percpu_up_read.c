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
struct percpu_rw_semaphore {int /*<<< orphan*/  writer; int /*<<< orphan*/ * read_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  __this_cpu_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcuwait_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smp_mb () ; 

void __percpu_up_read(struct percpu_rw_semaphore *sem)
{
	smp_mb(); /* B matches C */
	/*
	 * In other words, if they see our decrement (presumably to aggregate
	 * zero, as that is the only time it matters) they will also see our
	 * critical section.
	 */
	__this_cpu_dec(*sem->read_count);

	/* Prod writer to recheck readers_active */
	rcuwait_wake_up(&sem->writer);
}