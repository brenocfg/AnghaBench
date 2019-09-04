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
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_INTERRUPT ; 
 int /*<<< orphan*/  MSR_IA32_PACKAGE_THERM_STATUS ; 
 int /*<<< orphan*/  MSR_IA32_THERM_INTERRUPT ; 
 int /*<<< orphan*/  MSR_IA32_THERM_STATUS ; 
 scalar_t__ cpu_migrate (int) ; 
 scalar_t__ debug ; 
 scalar_t__ do_dts ; 
 scalar_t__ do_ptm ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  outf ; 
 unsigned int tcc_activation_temp ; 

int print_thermal(struct thread_data *t, struct core_data *c, struct pkg_data *p)
{
	unsigned long long msr;
	unsigned int dts, dts2;
	int cpu;

	if (!(do_dts || do_ptm))
		return 0;

	cpu = t->cpu_id;

	/* DTS is per-core, no need to print for each thread */
	if (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE))
		return 0;

	if (cpu_migrate(cpu)) {
		fprintf(outf, "Could not migrate to CPU %d\n", cpu);
		return -1;
	}

	if (do_ptm && (t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE)) {
		if (get_msr(cpu, MSR_IA32_PACKAGE_THERM_STATUS, &msr))
			return 0;

		dts = (msr >> 16) & 0x7F;
		fprintf(outf, "cpu%d: MSR_IA32_PACKAGE_THERM_STATUS: 0x%08llx (%d C)\n",
			cpu, msr, tcc_activation_temp - dts);

		if (get_msr(cpu, MSR_IA32_PACKAGE_THERM_INTERRUPT, &msr))
			return 0;

		dts = (msr >> 16) & 0x7F;
		dts2 = (msr >> 8) & 0x7F;
		fprintf(outf, "cpu%d: MSR_IA32_PACKAGE_THERM_INTERRUPT: 0x%08llx (%d C, %d C)\n",
			cpu, msr, tcc_activation_temp - dts, tcc_activation_temp - dts2);
	}


	if (do_dts && debug) {
		unsigned int resolution;

		if (get_msr(cpu, MSR_IA32_THERM_STATUS, &msr))
			return 0;

		dts = (msr >> 16) & 0x7F;
		resolution = (msr >> 27) & 0xF;
		fprintf(outf, "cpu%d: MSR_IA32_THERM_STATUS: 0x%08llx (%d C +/- %d)\n",
			cpu, msr, tcc_activation_temp - dts, resolution);

		if (get_msr(cpu, MSR_IA32_THERM_INTERRUPT, &msr))
			return 0;

		dts = (msr >> 16) & 0x7F;
		dts2 = (msr >> 8) & 0x7F;
		fprintf(outf, "cpu%d: MSR_IA32_THERM_INTERRUPT: 0x%08llx (%d C, %d C)\n",
			cpu, msr, tcc_activation_temp - dts, tcc_activation_temp - dts2);
	}

	return 0;
}