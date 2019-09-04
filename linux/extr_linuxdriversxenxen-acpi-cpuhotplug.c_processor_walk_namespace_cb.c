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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SYSTEM_NOTIFY ; 
 int /*<<< orphan*/  AE_CTRL_DEPTH ; 
 int /*<<< orphan*/  AE_OK ; 
#define  INSTALL_NOTIFY_HANDLER 129 
#define  UNINSTALL_NOTIFY_HANDLER 128 
 int /*<<< orphan*/  acpi_install_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_processor_hotplug_notify ; 
 int /*<<< orphan*/  acpi_remove_notify_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_processor_device (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
processor_walk_namespace_cb(acpi_handle handle,
			    u32 lvl, void *context, void **rv)
{
	acpi_status status;
	int *action = context;

	status = is_processor_device(handle);
	if (ACPI_FAILURE(status))
		return AE_OK;	/* not a processor; continue to walk */

	switch (*action) {
	case INSTALL_NOTIFY_HANDLER:
		acpi_install_notify_handler(handle,
					    ACPI_SYSTEM_NOTIFY,
					    acpi_processor_hotplug_notify,
					    NULL);
		break;
	case UNINSTALL_NOTIFY_HANDLER:
		acpi_remove_notify_handler(handle,
					   ACPI_SYSTEM_NOTIFY,
					   acpi_processor_hotplug_notify);
		break;
	default:
		break;
	}

	/* found a processor; skip walking underneath */
	return AE_CTRL_DEPTH;
}