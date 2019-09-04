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
struct msr_hwp_request {int dummy; } ;
struct msr_hwp_cap {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_HWP_CAPABILITIES ; 
 int /*<<< orphan*/  MSR_HWP_REQUEST ; 
 int /*<<< orphan*/  MSR_IA32_ENERGY_PERF_BIAS ; 
 int /*<<< orphan*/  get_msr (int,int /*<<< orphan*/ ,unsigned long long*) ; 
 scalar_t__ has_epb ; 
 int /*<<< orphan*/  has_hwp ; 
 int /*<<< orphan*/  print_hwp_cap (int,struct msr_hwp_cap*,char*) ; 
 int /*<<< orphan*/  print_hwp_request (int,struct msr_hwp_request*,char*) ; 
 int /*<<< orphan*/  printf (char*,int,unsigned int) ; 
 int /*<<< orphan*/  read_hwp_cap (int,struct msr_hwp_cap*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_hwp_request (int,struct msr_hwp_request*,int /*<<< orphan*/ ) ; 

int print_cpu_msrs(int cpu)
{
	unsigned long long msr;
	struct msr_hwp_request req;
	struct msr_hwp_cap cap;

	if (has_epb) {
		get_msr(cpu, MSR_IA32_ENERGY_PERF_BIAS, &msr);

		printf("cpu%d: EPB %u\n", cpu, (unsigned int) msr);
	}

	if (!has_hwp)
		return 0;

	read_hwp_request(cpu, &req, MSR_HWP_REQUEST);
	print_hwp_request(cpu, &req, "");

	read_hwp_cap(cpu, &cap, MSR_HWP_CAPABILITIES);
	print_hwp_cap(cpu, &cap, "");

	return 0;
}