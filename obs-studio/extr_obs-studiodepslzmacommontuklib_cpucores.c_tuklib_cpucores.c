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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

extern uint32_t
tuklib_cpucores(void)
{
	uint32_t ret = 0;

#if defined(TUKLIB_CPUCORES_SYSCTL)
	int name[2] = { CTL_HW, HW_NCPU };
	int cpus;
	size_t cpus_size = sizeof(cpus);
	if (sysctl(name, 2, &cpus, &cpus_size, NULL, 0) != -1
			&& cpus_size == sizeof(cpus) && cpus > 0)
		ret = cpus;

#elif defined(TUKLIB_CPUCORES_SYSCONF)
#	ifdef _SC_NPROCESSORS_ONLN
	// Most systems
	const long cpus = sysconf(_SC_NPROCESSORS_ONLN);
#	else
	// IRIX
	const long cpus = sysconf(_SC_NPROC_ONLN);
#	endif
	if (cpus > 0)
		ret = cpus;

#elif defined(TUKLIB_CPUCORES_PSTAT_GETDYNAMIC)
	struct pst_dynamic pst;
	if (pstat_getdynamic(&pst, sizeof(pst), 1, 0) != -1)
		ret = pst.psd_proc_cnt;
#endif

	return ret;
}