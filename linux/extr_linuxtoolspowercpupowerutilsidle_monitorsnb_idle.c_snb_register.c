#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct cpuidle_monitor {int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; } ;
struct TYPE_2__ {scalar_t__ vendor; int family; int model; } ;

/* Variables and functions */
 int SNB_CSTATE_COUNT ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 void* calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_count ; 
 TYPE_1__ cpupower_cpu_info ; 
 void** current_count ; 
 struct cpuidle_monitor intel_snb_monitor ; 
 void* is_valid ; 
 void** previous_count ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cpuidle_monitor *snb_register(void)
{
	int num;

	if (cpupower_cpu_info.vendor != X86_VENDOR_INTEL
	    || cpupower_cpu_info.family != 6)
		return NULL;

	switch (cpupower_cpu_info.model) {
	case 0x2A: /* SNB */
	case 0x2D: /* SNB Xeon */
	case 0x3A: /* IVB */
	case 0x3E: /* IVB Xeon */
	case 0x3C: /* HSW */
	case 0x3F: /* HSW */
	case 0x45: /* HSW */
	case 0x46: /* HSW */
		break;
	default:
		return NULL;
	}

	is_valid = calloc(cpu_count, sizeof(int));
	for (num = 0; num < SNB_CSTATE_COUNT; num++) {
		previous_count[num] = calloc(cpu_count,
					sizeof(unsigned long long));
		current_count[num]  = calloc(cpu_count,
					sizeof(unsigned long long));
	}
	intel_snb_monitor.name_len = strlen(intel_snb_monitor.name);
	return &intel_snb_monitor;
}