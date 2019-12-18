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

__attribute__((used)) static inline int kallsyms_for_perf(void)
{
#ifdef CONFIG_PERF_EVENTS
	extern int sysctl_perf_event_paranoid;
	if (sysctl_perf_event_paranoid <= 1)
		return 1;
#endif
	return 0;
}