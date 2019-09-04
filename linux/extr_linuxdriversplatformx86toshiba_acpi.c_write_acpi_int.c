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
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 scalar_t__ AE_OK ; 
 int EIO ; 
 scalar_t__ acpi_execute_simple_method (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int write_acpi_int(const char *methodName, int val)
{
	acpi_status status;

	status = acpi_execute_simple_method(NULL, (char *)methodName, val);
	return (status == AE_OK) ? 0 : -EIO;
}