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
struct acpi_device {int /*<<< orphan*/  handle; } ;
typedef  enum rbtn_type { ____Placeholder_rbtn_type } rbtn_type ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int RBTN_SLIDER ; 
 int RBTN_TOGGLE ; 
 int RBTN_UNKNOWN ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 

__attribute__((used)) static enum rbtn_type rbtn_check(struct acpi_device *device)
{
	unsigned long long output;
	acpi_status status;

	status = acpi_evaluate_integer(device->handle, "CRBT", NULL, &output);
	if (ACPI_FAILURE(status))
		return RBTN_UNKNOWN;

	switch (output) {
	case 0:
	case 1:
		return RBTN_TOGGLE;
	case 2:
	case 3:
		return RBTN_SLIDER;
	default:
		return RBTN_UNKNOWN;
	}
}