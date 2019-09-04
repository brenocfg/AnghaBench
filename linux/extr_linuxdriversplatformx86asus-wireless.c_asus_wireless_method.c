#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  type; } ;
typedef  int u64 ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
typedef  int /*<<< orphan*/  acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_object_list*,int*) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  acpi_handle_err (int /*<<< orphan*/ ,char*,char const*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status asus_wireless_method(acpi_handle handle, const char *method,
					int param, u64 *ret)
{
	struct acpi_object_list p;
	union acpi_object obj;
	acpi_status s;

	acpi_handle_debug(handle, "Evaluating method %s, parameter %#x\n",
			  method, param);
	obj.type = ACPI_TYPE_INTEGER;
	obj.integer.value = param;
	p.count = 1;
	p.pointer = &obj;

	s = acpi_evaluate_integer(handle, (acpi_string) method, &p, ret);
	if (ACPI_FAILURE(s))
		acpi_handle_err(handle,
				"Failed to eval method %s, param %#x (%d)\n",
				method, param, s);
	else
		acpi_handle_debug(handle, "%s returned %#llx\n", method, *ret);

	return s;
}