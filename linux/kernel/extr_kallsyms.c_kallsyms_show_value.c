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
 int /*<<< orphan*/  CAP_SYSLOG ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  has_capability_noaudit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kallsyms_for_perf () ; 
 int kptr_restrict ; 

int kallsyms_show_value(void)
{
	switch (kptr_restrict) {
	case 0:
		if (kallsyms_for_perf())
			return 1;
	/* fallthrough */
	case 1:
		if (has_capability_noaudit(current, CAP_SYSLOG))
			return 1;
	/* fallthrough */
	default:
		return 0;
	}
}