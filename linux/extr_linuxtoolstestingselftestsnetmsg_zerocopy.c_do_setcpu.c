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
typedef  int /*<<< orphan*/  mask ;
typedef  int /*<<< orphan*/  cpu_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ cfg_verbose ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ sched_setaffinity (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static int do_setcpu(int cpu)
{
	cpu_set_t mask;

	CPU_ZERO(&mask);
	CPU_SET(cpu, &mask);
	if (sched_setaffinity(0, sizeof(mask), &mask))
		error(1, 0, "setaffinity %d", cpu);

	if (cfg_verbose)
		fprintf(stderr, "cpu: %u\n", cpu);

	return 0;
}