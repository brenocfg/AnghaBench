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
typedef  scalar_t__ u32 ;

/* Variables and functions */
 int ENODATA ; 
 int EOVERFLOW ; 
 int /*<<< orphan*/  PCI_PROBE_ONLY ; 
 int /*<<< orphan*/  of_chosen ; 
 int of_property_read_u32 (int /*<<< orphan*/ ,char*,scalar_t__*) ; 
 int /*<<< orphan*/  pci_add_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pci_clear_flags (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,char*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 

void of_pci_check_probe_only(void)
{
	u32 val;
	int ret;

	ret = of_property_read_u32(of_chosen, "linux,pci-probe-only", &val);
	if (ret) {
		if (ret == -ENODATA || ret == -EOVERFLOW)
			pr_warn("linux,pci-probe-only without valid value, ignoring\n");
		return;
	}

	if (val)
		pci_add_flags(PCI_PROBE_ONLY);
	else
		pci_clear_flags(PCI_PROBE_ONLY);

	pr_info("PROBE_ONLY %sabled\n", val ? "en" : "dis");
}