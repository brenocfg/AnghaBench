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
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int write_acpi_int_ret (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int write_acpi_int(acpi_handle handle, const char *method, int val)
{
	return write_acpi_int_ret(handle, method, val, NULL);
}