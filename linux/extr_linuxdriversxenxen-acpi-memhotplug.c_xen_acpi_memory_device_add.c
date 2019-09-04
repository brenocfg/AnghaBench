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
struct acpi_memory_device {struct acpi_device* device; int /*<<< orphan*/  res_list; } ;
struct acpi_device {struct acpi_memory_device* driver_data; } ;

/* Variables and functions */
 char* ACPI_MEMORY_DEVICE_CLASS ; 
 char* ACPI_MEMORY_DEVICE_NAME ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_device_class (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_device_name (struct acpi_device*) ; 
 int /*<<< orphan*/  acpi_hotmem_initialized ; 
 int /*<<< orphan*/  acpi_memory_check_device (struct acpi_memory_device*) ; 
 int acpi_memory_get_device_resources (struct acpi_memory_device*) ; 
 int /*<<< orphan*/  kfree (struct acpi_memory_device*) ; 
 struct acpi_memory_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int xen_acpi_memory_enable_device (struct acpi_memory_device*) ; 

__attribute__((used)) static int xen_acpi_memory_device_add(struct acpi_device *device)
{
	int result;
	struct acpi_memory_device *mem_device = NULL;


	if (!device)
		return -EINVAL;

	mem_device = kzalloc(sizeof(struct acpi_memory_device), GFP_KERNEL);
	if (!mem_device)
		return -ENOMEM;

	INIT_LIST_HEAD(&mem_device->res_list);
	mem_device->device = device;
	sprintf(acpi_device_name(device), "%s", ACPI_MEMORY_DEVICE_NAME);
	sprintf(acpi_device_class(device), "%s", ACPI_MEMORY_DEVICE_CLASS);
	device->driver_data = mem_device;

	/* Get the range from the _CRS */
	result = acpi_memory_get_device_resources(mem_device);
	if (result) {
		kfree(mem_device);
		return result;
	}

	/*
	 * For booting existed memory devices, early boot code has recognized
	 * memory area by EFI/E820. If DSDT shows these memory devices on boot,
	 * hotplug is not necessary for them.
	 * For hot-added memory devices during runtime, it need hypercall to
	 * Xen hypervisor to add memory.
	 */
	if (!acpi_hotmem_initialized)
		return 0;

	if (!acpi_memory_check_device(mem_device))
		result = xen_acpi_memory_enable_device(mem_device);

	return result;
}