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
struct cpuid_core_info {scalar_t__ pkg; scalar_t__ core; scalar_t__ cpu; } ;

/* Variables and functions */

__attribute__((used)) static int __compare(const void *t1, const void *t2)
{
	struct cpuid_core_info *top1 = (struct cpuid_core_info *)t1;
	struct cpuid_core_info *top2 = (struct cpuid_core_info *)t2;
	if (top1->pkg < top2->pkg)
		return -1;
	else if (top1->pkg > top2->pkg)
		return 1;
	else if (top1->core < top2->core)
		return -1;
	else if (top1->core > top2->core)
		return 1;
	else if (top1->cpu < top2->cpu)
		return -1;
	else if (top1->cpu > top2->cpu)
		return 1;
	else
		return 0;
}