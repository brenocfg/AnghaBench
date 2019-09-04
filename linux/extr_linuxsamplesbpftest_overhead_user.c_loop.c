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
typedef  int /*<<< orphan*/  cpuset ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_task_rename (int) ; 
 int /*<<< orphan*/  test_urandom_read (int) ; 

__attribute__((used)) static void loop(int cpu, int flags)
{
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);
	CPU_SET(cpu, &cpuset);
	sched_setaffinity(0, sizeof(cpuset), &cpuset);

	if (flags & 1)
		test_task_rename(cpu);
	if (flags & 2)
		test_urandom_read(cpu);
}