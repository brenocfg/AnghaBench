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
struct thread_data {int flags; int cpu_id; } ;
struct pkg_data {int dummy; } ;
struct core_data {int dummy; } ;

/* Variables and functions */
 int CPU_IS_FIRST_CORE_IN_PACKAGE ; 
 int CPU_IS_FIRST_THREAD_IN_CORE ; 
 int /*<<< orphan*/  MSR_DRAM_POWER_INFO ; 
 int /*<<< orphan*/  MSR_DRAM_POWER_LIMIT ; 
 int /*<<< orphan*/  MSR_PKG_POWER_INFO ; 
 int /*<<< orphan*/  MSR_PKG_POWER_LIMIT ; 
 int /*<<< orphan*/  MSR_PP0_POLICY ; 
 int /*<<< orphan*/  MSR_PP0_POWER_LIMIT ; 
 int /*<<< orphan*/  MSR_PP1_POLICY ; 
 int /*<<< orphan*/  MSR_PP1_POWER_LIMIT ; 
 int /*<<< orphan*/  MSR_RAPL_POWER_UNIT ; 
 int /*<<< orphan*/  MSR_RAPL_PWR_UNIT ; 
 int RAPL_AMD_F17H ; 
 int RAPL_CORES_POWER_LIMIT ; 
 int RAPL_CORE_POLICY ; 
 int RAPL_DRAM ; 
 int RAPL_DRAM_POWER_INFO ; 
 int RAPL_GFX ; 
 int RAPL_PKG ; 
 int RAPL_PKG_POWER_INFO ; 
 unsigned long long RAPL_POWER_GRANULARITY ; 
 unsigned long long RAPL_TIME_GRANULARITY ; 
 scalar_t__ cpu_migrate (int) ; 
 int do_rapl ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,...) ; 
 scalar_t__ get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 int /*<<< orphan*/  outf ; 
 int /*<<< orphan*/  print_power_limit_msr (int,unsigned long long,char*) ; 
 int /*<<< orphan*/  rapl_energy_units ; 
 unsigned long long rapl_power_units ; 
 unsigned long long rapl_time_units ; 

int print_rapl(struct thread_data *t, struct core_data *c, struct pkg_data *p)
{
	unsigned long long msr;
	const char *msr_name;
	int cpu;

	if (!do_rapl)
		return 0;

	/* RAPL counters are per package, so print only for 1st thread/package */
	if (!(t->flags & CPU_IS_FIRST_THREAD_IN_CORE) || !(t->flags & CPU_IS_FIRST_CORE_IN_PACKAGE))
		return 0;

	cpu = t->cpu_id;
	if (cpu_migrate(cpu)) {
		fprintf(outf, "Could not migrate to CPU %d\n", cpu);
		return -1;
	}

	if (do_rapl & RAPL_AMD_F17H) {
		msr_name = "MSR_RAPL_PWR_UNIT";
		if (get_msr(cpu, MSR_RAPL_PWR_UNIT, &msr))
			return -1;
	} else {
		msr_name = "MSR_RAPL_POWER_UNIT";
		if (get_msr(cpu, MSR_RAPL_POWER_UNIT, &msr))
			return -1;
	}

	fprintf(outf, "cpu%d: %s: 0x%08llx (%f Watts, %f Joules, %f sec.)\n", cpu, msr_name, msr,
		rapl_power_units, rapl_energy_units, rapl_time_units);

	if (do_rapl & RAPL_PKG_POWER_INFO) {

		if (get_msr(cpu, MSR_PKG_POWER_INFO, &msr))
                	return -5;


		fprintf(outf, "cpu%d: MSR_PKG_POWER_INFO: 0x%08llx (%.0f W TDP, RAPL %.0f - %.0f W, %f sec.)\n",
			cpu, msr,
			((msr >>  0) & RAPL_POWER_GRANULARITY) * rapl_power_units,
			((msr >> 16) & RAPL_POWER_GRANULARITY) * rapl_power_units,
			((msr >> 32) & RAPL_POWER_GRANULARITY) * rapl_power_units,
			((msr >> 48) & RAPL_TIME_GRANULARITY) * rapl_time_units);

	}
	if (do_rapl & RAPL_PKG) {

		if (get_msr(cpu, MSR_PKG_POWER_LIMIT, &msr))
			return -9;

		fprintf(outf, "cpu%d: MSR_PKG_POWER_LIMIT: 0x%08llx (%slocked)\n",
			cpu, msr, (msr >> 63) & 1 ? "" : "UN");

		print_power_limit_msr(cpu, msr, "PKG Limit #1");
		fprintf(outf, "cpu%d: PKG Limit #2: %sabled (%f Watts, %f* sec, clamp %sabled)\n",
			cpu,
			((msr >> 47) & 1) ? "EN" : "DIS",
			((msr >> 32) & 0x7FFF) * rapl_power_units,
			(1.0 + (((msr >> 54) & 0x3)/4.0)) * (1 << ((msr >> 49) & 0x1F)) * rapl_time_units,
			((msr >> 48) & 1) ? "EN" : "DIS");
	}

	if (do_rapl & RAPL_DRAM_POWER_INFO) {
		if (get_msr(cpu, MSR_DRAM_POWER_INFO, &msr))
                	return -6;

		fprintf(outf, "cpu%d: MSR_DRAM_POWER_INFO,: 0x%08llx (%.0f W TDP, RAPL %.0f - %.0f W, %f sec.)\n",
			cpu, msr,
			((msr >>  0) & RAPL_POWER_GRANULARITY) * rapl_power_units,
			((msr >> 16) & RAPL_POWER_GRANULARITY) * rapl_power_units,
			((msr >> 32) & RAPL_POWER_GRANULARITY) * rapl_power_units,
			((msr >> 48) & RAPL_TIME_GRANULARITY) * rapl_time_units);
	}
	if (do_rapl & RAPL_DRAM) {
		if (get_msr(cpu, MSR_DRAM_POWER_LIMIT, &msr))
			return -9;
		fprintf(outf, "cpu%d: MSR_DRAM_POWER_LIMIT: 0x%08llx (%slocked)\n",
				cpu, msr, (msr >> 31) & 1 ? "" : "UN");

		print_power_limit_msr(cpu, msr, "DRAM Limit");
	}
	if (do_rapl & RAPL_CORE_POLICY) {
		if (get_msr(cpu, MSR_PP0_POLICY, &msr))
			return -7;

		fprintf(outf, "cpu%d: MSR_PP0_POLICY: %lld\n", cpu, msr & 0xF);
	}
	if (do_rapl & RAPL_CORES_POWER_LIMIT) {
		if (get_msr(cpu, MSR_PP0_POWER_LIMIT, &msr))
			return -9;
		fprintf(outf, "cpu%d: MSR_PP0_POWER_LIMIT: 0x%08llx (%slocked)\n",
				cpu, msr, (msr >> 31) & 1 ? "" : "UN");
		print_power_limit_msr(cpu, msr, "Cores Limit");
	}
	if (do_rapl & RAPL_GFX) {
		if (get_msr(cpu, MSR_PP1_POLICY, &msr))
			return -8;

		fprintf(outf, "cpu%d: MSR_PP1_POLICY: %lld\n", cpu, msr & 0xF);

		if (get_msr(cpu, MSR_PP1_POWER_LIMIT, &msr))
			return -9;
		fprintf(outf, "cpu%d: MSR_PP1_POWER_LIMIT: 0x%08llx (%slocked)\n",
				cpu, msr, (msr >> 31) & 1 ? "" : "UN");
		print_power_limit_msr(cpu, msr, "GFX Limit");
	}
	return 0;
}