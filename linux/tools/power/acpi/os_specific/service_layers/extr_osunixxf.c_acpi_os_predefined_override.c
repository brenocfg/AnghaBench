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
struct acpi_predefined_names {int dummy; } ;
typedef  int /*<<< orphan*/ * acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 

acpi_status
acpi_os_predefined_override(const struct acpi_predefined_names *init_val,
			    acpi_string *new_val)
{

	if (!init_val || !new_val) {
		return (AE_BAD_PARAMETER);
	}

	*new_val = NULL;
	return (AE_OK);
}