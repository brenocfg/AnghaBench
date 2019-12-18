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

/* Variables and functions */
 int /*<<< orphan*/  MSR_IA32_PERF_STATUS ; 
 int /*<<< orphan*/  decode (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rdmsr (unsigned int,int /*<<< orphan*/ ,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int decode_live(unsigned int cpu)
{
	unsigned int lo, hi;
	int err;

	err = rdmsr(cpu, MSR_IA32_PERF_STATUS, &lo, &hi);

	if (err) {
		printf("can't get MSR_IA32_PERF_STATUS for cpu %d\n", cpu);
		printf("Possible trouble: you don't run an Enhanced SpeedStep capable cpu\n");
		printf("or you are not root, or the msr driver is not present\n");
		return 1;
	}

	decode(lo);

	return 0;
}