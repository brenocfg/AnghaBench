#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  en; } ;
struct TYPE_3__ {int /*<<< orphan*/  en; } ;
union msr_pstate {unsigned long long val; TYPE_2__ bits; TYPE_1__ fam17h_bits; } ;

/* Variables and functions */
 int MAX_HW_PSTATES ; 
 scalar_t__ MSR_AMD_PSTATE ; 
 scalar_t__ MSR_AMD_PSTATE_LIMIT ; 
 scalar_t__ MSR_AMD_PSTATE_STATUS ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 unsigned long get_cof (unsigned int,union msr_pstate) ; 
 scalar_t__ read_msr (unsigned int,scalar_t__,unsigned long long*) ; 
 int /*<<< orphan*/  stderr ; 

int decode_pstates(unsigned int cpu, unsigned int cpu_family,
		   int boost_states, unsigned long *pstates, int *no)
{
	int i, psmax, pscur;
	union msr_pstate pstate;
	unsigned long long val;

	/* Only read out frequencies from HW when CPU might be boostable
	   to keep the code as short and clean as possible.
	   Otherwise frequencies are exported via ACPI tables.
	*/
	if (cpu_family < 0x10 || cpu_family == 0x14)
		return -1;

	if (read_msr(cpu, MSR_AMD_PSTATE_LIMIT, &val))
		return -1;

	psmax = (val >> 4) & 0x7;

	if (read_msr(cpu, MSR_AMD_PSTATE_STATUS, &val))
		return -1;

	pscur = val & 0x7;

	pscur += boost_states;
	psmax += boost_states;
	for (i = 0; i <= psmax; i++) {
		if (i >= MAX_HW_PSTATES) {
			fprintf(stderr, "HW pstates [%d] exceeding max [%d]\n",
				psmax, MAX_HW_PSTATES);
			return -1;
		}
		if (read_msr(cpu, MSR_AMD_PSTATE + i, &pstate.val))
			return -1;
		if ((cpu_family == 0x17) && (!pstate.fam17h_bits.en))
			continue;
		else if (!pstate.bits.en)
			continue;

		pstates[i] = get_cof(cpu_family, pstate);
	}
	*no = i;
	return 0;
}