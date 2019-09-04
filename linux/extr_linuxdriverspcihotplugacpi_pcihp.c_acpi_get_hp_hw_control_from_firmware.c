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
struct pci_host_bridge {scalar_t__ native_shpc_hotplug; int /*<<< orphan*/  dev; } ;
struct pci_dev {struct pci_bus* bus; int /*<<< orphan*/  dev; } ;
struct pci_bus {struct pci_bus* parent; } ;
struct acpi_pci_root {scalar_t__ osc_support_set; } ;
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FULL_PATHNAME ; 
 scalar_t__ ACPI_HANDLE (int /*<<< orphan*/ *) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_get_name (scalar_t__,int /*<<< orphan*/ ,struct acpi_buffer*) ; 
 int /*<<< orphan*/  acpi_get_parent (scalar_t__,scalar_t__*) ; 
 scalar_t__ acpi_is_root_bridge (scalar_t__) ; 
 struct acpi_pci_root* acpi_pci_find_root (scalar_t__) ; 
 scalar_t__ acpi_pci_get_bridge_handle (struct pci_bus*) ; 
 int /*<<< orphan*/  acpi_run_oshp (scalar_t__) ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 struct pci_host_bridge* pci_find_host_bridge (struct pci_bus*) ; 
 int /*<<< orphan*/  pci_info (struct pci_dev*,char*,...) ; 

int acpi_get_hp_hw_control_from_firmware(struct pci_dev *pdev)
{
	const struct pci_host_bridge *host;
	const struct acpi_pci_root *root;
	acpi_status status;
	acpi_handle chandle, handle;
	struct acpi_buffer string = { ACPI_ALLOCATE_BUFFER, NULL };

	/*
	 * If there's no ACPI host bridge (i.e., ACPI support is compiled
	 * into the kernel but the hardware platform doesn't support ACPI),
	 * there's nothing to do here.
	 */
	host = pci_find_host_bridge(pdev->bus);
	root = acpi_pci_find_root(ACPI_HANDLE(&host->dev));
	if (!root)
		return 0;

	/*
	 * If _OSC exists, it determines whether we're allowed to manage
	 * the SHPC.  We executed it while enumerating the host bridge.
	 */
	if (root->osc_support_set) {
		if (host->native_shpc_hotplug)
			return 0;
		return -ENODEV;
	}

	/*
	 * In the absence of _OSC, we're always allowed to manage the SHPC.
	 * However, if an OSHP method is present, we must execute it so the
	 * firmware can transfer control to the OS, e.g., direct interrupts
	 * to the OS instead of to the firmware.
	 *
	 * N.B. The PCI Firmware Spec (r3.2, sec 4.8) does not endorse
	 * searching up the ACPI hierarchy, so the loops below are suspect.
	 */
	handle = ACPI_HANDLE(&pdev->dev);
	if (!handle) {
		/*
		 * This hotplug controller was not listed in the ACPI name
		 * space at all. Try to get ACPI handle of parent PCI bus.
		 */
		struct pci_bus *pbus;
		for (pbus = pdev->bus; pbus; pbus = pbus->parent) {
			handle = acpi_pci_get_bridge_handle(pbus);
			if (handle)
				break;
		}
	}

	while (handle) {
		acpi_get_name(handle, ACPI_FULL_PATHNAME, &string);
		pci_info(pdev, "Requesting control of SHPC hotplug via OSHP (%s)\n",
			 (char *)string.pointer);
		status = acpi_run_oshp(handle);
		if (ACPI_SUCCESS(status))
			goto got_one;
		if (acpi_is_root_bridge(handle))
			break;
		chandle = handle;
		status = acpi_get_parent(chandle, &handle);
		if (ACPI_FAILURE(status))
			break;
	}

	pci_info(pdev, "Cannot get control of SHPC hotplug\n");
	kfree(string.pointer);
	return -ENODEV;
got_one:
	pci_info(pdev, "Gained control of SHPC hotplug (%s)\n",
		 (char *)string.pointer);
	kfree(string.pointer);
	return 0;
}