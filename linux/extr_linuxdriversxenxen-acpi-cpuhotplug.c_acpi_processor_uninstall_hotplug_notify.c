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
 int /*<<< orphan*/  ACPI_ROOT_OBJECT ; 
 int /*<<< orphan*/  ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  ACPI_UINT32_MAX ; 
 int UNINSTALL_NOTIFY_HANDLER ; 
 int /*<<< orphan*/  acpi_walk_namespace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  processor_walk_namespace_cb ; 

__attribute__((used)) static
void acpi_processor_uninstall_hotplug_notify(void)
{
	int action = UNINSTALL_NOTIFY_HANDLER;
	acpi_walk_namespace(ACPI_TYPE_ANY,
			    ACPI_ROOT_OBJECT,
			    ACPI_UINT32_MAX,
			    processor_walk_namespace_cb, NULL, &action, NULL);
}