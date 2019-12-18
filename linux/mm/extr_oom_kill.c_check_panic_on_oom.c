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
struct oom_control {scalar_t__ constraint; } ;

/* Variables and functions */
 scalar_t__ CONSTRAINT_NONE ; 
 int /*<<< orphan*/  dump_header (struct oom_control*,int /*<<< orphan*/ *) ; 
 scalar_t__ is_sysrq_oom (struct oom_control*) ; 
 scalar_t__ likely (int) ; 
 int /*<<< orphan*/  panic (char*,char*) ; 
 int sysctl_panic_on_oom ; 

__attribute__((used)) static void check_panic_on_oom(struct oom_control *oc)
{
	if (likely(!sysctl_panic_on_oom))
		return;
	if (sysctl_panic_on_oom != 2) {
		/*
		 * panic_on_oom == 1 only affects CONSTRAINT_NONE, the kernel
		 * does not panic for cpuset, mempolicy, or memcg allocation
		 * failures.
		 */
		if (oc->constraint != CONSTRAINT_NONE)
			return;
	}
	/* Do not panic for oom kills triggered by sysrq */
	if (is_sysrq_oom(oc))
		return;
	dump_header(oc, NULL);
	panic("Out of memory: %s panic_on_oom is enabled\n",
		sysctl_panic_on_oom == 2 ? "compulsory" : "system-wide");
}