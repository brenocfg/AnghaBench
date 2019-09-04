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
typedef  int u64 ;
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ENODEV ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_err (char*) ; 

__attribute__((used)) static int topstar_acpi_fncx_switch(struct acpi_device *device, bool state)
{
	acpi_status status;
	u64 arg = state ? 0x86 : 0x87;

	status = acpi_execute_simple_method(device->handle, "FNCX", arg);
	if (ACPI_FAILURE(status)) {
		pr_err("Unable to switch FNCX notifications\n");
		return -ENODEV;
	}

	return 0;
}