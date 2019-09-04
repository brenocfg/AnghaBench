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
 int /*<<< orphan*/  POLICY_DEFAULT ; 
 int aspm_disabled ; 
 int /*<<< orphan*/  aspm_force ; 
 int /*<<< orphan*/  aspm_policy ; 

void pcie_no_aspm(void)
{
	/*
	 * Disabling ASPM is intended to prevent the kernel from modifying
	 * existing hardware state, not to clear existing state. To that end:
	 * (a) set policy to POLICY_DEFAULT in order to avoid changing state
	 * (b) prevent userspace from changing policy
	 */
	if (!aspm_force) {
		aspm_policy = POLICY_DEFAULT;
		aspm_disabled = 1;
	}
}