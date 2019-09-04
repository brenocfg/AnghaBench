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
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_execute_simple_method (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int method_int1(acpi_handle handle, char *method, int cmd)
{
	acpi_status status;

	status = acpi_execute_simple_method(handle, method, cmd);
	return ACPI_FAILURE(status) ? -1 : 0;
}