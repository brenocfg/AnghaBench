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
struct percpu_rw_semaphore {int /*<<< orphan*/ * read_count; } ;

/* Variables and functions */
 scalar_t__ per_cpu_sum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_mb () ; 

__attribute__((used)) static bool readers_active_check(struct percpu_rw_semaphore *sem)
{
	if (per_cpu_sum(*sem->read_count) != 0)
		return false;

	/*
	 * If we observed the decrement; ensure we see the entire critical
	 * section.
	 */

	smp_mb(); /* C matches B */

	return true;
}