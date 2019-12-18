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
struct cpuidle_monitor {int hw_states_num; int /*<<< orphan*/  name; int /*<<< orphan*/  name_len; } ;
struct TYPE_2__ {scalar_t__ vendor; int family; } ;

/* Variables and functions */
 int AMD_FAM14H_STATE_NUM ; 
 scalar_t__ MONITOR_NAME_LEN ; 
 scalar_t__ X86_VENDOR_AMD ; 
 struct cpuidle_monitor amd_fam14h_monitor ; 
 int /*<<< orphan*/ * amd_fam14h_pci_dev ; 
 void* calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cpu_count ; 
 TYPE_1__ cpupower_cpu_info ; 
 void** current_count ; 
 int /*<<< orphan*/  is_nbp1_capable () ; 
 int /*<<< orphan*/ * pci_acc ; 
 int /*<<< orphan*/ * pci_slot_func_init (int /*<<< orphan*/ **,int,int) ; 
 void** previous_count ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char*,scalar_t__) ; 

struct cpuidle_monitor *amd_fam14h_register(void)
{
	int num;

	if (cpupower_cpu_info.vendor != X86_VENDOR_AMD)
		return NULL;

	if (cpupower_cpu_info.family == 0x14)
		strncpy(amd_fam14h_monitor.name, "Fam_14h",
			MONITOR_NAME_LEN - 1);
	else if (cpupower_cpu_info.family == 0x12)
		strncpy(amd_fam14h_monitor.name, "Fam_12h",
			MONITOR_NAME_LEN - 1);
	else
		return NULL;

	/* We do not alloc for nbp1 machine wide counter */
	for (num = 0; num < AMD_FAM14H_STATE_NUM - 1; num++) {
		previous_count[num] = calloc(cpu_count,
					      sizeof(unsigned long long));
		current_count[num]  = calloc(cpu_count,
					      sizeof(unsigned long long));
	}

	/* We need PCI device: Slot 18, Func 6, compare with BKDG
	   for fam 12h/14h */
	amd_fam14h_pci_dev = pci_slot_func_init(&pci_acc, 0x18, 6);
	if (amd_fam14h_pci_dev == NULL || pci_acc == NULL)
		return NULL;

	if (!is_nbp1_capable())
		amd_fam14h_monitor.hw_states_num = AMD_FAM14H_STATE_NUM - 1;

	amd_fam14h_monitor.name_len = strlen(amd_fam14h_monitor.name);
	return &amd_fam14h_monitor;
}