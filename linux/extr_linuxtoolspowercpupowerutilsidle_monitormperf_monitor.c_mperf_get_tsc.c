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
 int /*<<< orphan*/  MSR_TSC ; 
 int /*<<< orphan*/  base_cpu ; 
 int /*<<< orphan*/  dprint (char*,unsigned long long) ; 
 int read_msr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long*) ; 

__attribute__((used)) static int mperf_get_tsc(unsigned long long *tsc)
{
	int ret;

	ret = read_msr(base_cpu, MSR_TSC, tsc);
	if (ret)
		dprint("Reading TSC MSR failed, returning %llu\n", *tsc);
	return ret;
}