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
struct thread_data {int cpu_id; int flags; } ;
struct pkg_data {int dummy; } ;
struct core_data {int dummy; } ;

/* Variables and functions */
 int CPU_IS_FIRST_CORE_IN_PACKAGE ; 
 int CPU_IS_FIRST_THREAD_IN_CORE ; 
#define  ENERGY_PERF_BIAS_NORMAL 130 
#define  ENERGY_PERF_BIAS_PERFORMANCE 129 
#define  ENERGY_PERF_BIAS_POWERSAVE 128 
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 scalar_t__ cpu_migrate (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  has_epb ; 
 int /*<<< orphan*/  outf ; 

int print_epb(struct thread_data *t, struct core_data *c, struct pkg_data *p)
{
	unsigned long long msr;
	char *epb_string;
	int cpu;

	if (!has_epb)
		return 0;

	cpu = t->cpu_id;

	/* EPB is per-package */
	if (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE) || !(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		return 0;

	if (cpu_migrate(cpu)) {
		fprintf(outf, "Could not migrate to CPU %d\n", cpu);
		return -1;
	}

	if (get_msr(cpu, MSR_IA32_ENERGY_PERF_BIAS, &msr))
		return 0;

	switch (msr & 0xF) {
	case ENERGY_PERF_BIAS_PERFORMANCE:
		epb_string = "performance";
		break;
	case ENERGY_PERF_BIAS_NORMAL:
		epb_string = "balanced";
		break;
	case ENERGY_PERF_BIAS_POWERSAVE:
		epb_string = "powersave";
		break;
	default:
		epb_string = "custom";
		break;
	}
	fprintf(outf, "cpu%d: MSR_IA32_ENERGY_PERF_BIAS: 0x%08llx (%s)\n", cpu, msr, epb_string);

	return 0;
}