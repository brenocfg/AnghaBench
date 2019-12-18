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
typedef  int /*<<< orphan*/  cpu_set_t ;
typedef  int /*<<< orphan*/  __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK (int,char*,char*,int,int) ; 
 int /*<<< orphan*/  CPU_SET (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void on_sample(void *ctx, int cpu, void *data, __u32 size)
{
	int cpu_data = *(int *)data, duration = 0;
	cpu_set_t *cpu_seen = ctx;

	if (cpu_data != cpu)
		CHECK(cpu_data != cpu, "check_cpu_data",
		      "cpu_data %d != cpu %d\n", cpu_data, cpu);

	CPU_SET(cpu, cpu_seen);
}