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
struct perf_kvm_stat {char* exit_reasons_isa; int /*<<< orphan*/  exit_reasons; } ;

/* Variables and functions */
 int ENOTSUP ; 
 int /*<<< orphan*/  sie_exit_reasons ; 
 scalar_t__ strstr (char const*,char*) ; 

int cpu_isa_init(struct perf_kvm_stat *kvm, const char *cpuid)
{
	if (strstr(cpuid, "IBM")) {
		kvm->exit_reasons = sie_exit_reasons;
		kvm->exit_reasons_isa = "SIE";
	} else
		return -ENOTSUP;

	return 0;
}