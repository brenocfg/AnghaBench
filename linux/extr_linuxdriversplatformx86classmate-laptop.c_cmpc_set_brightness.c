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
union acpi_object {TYPE_1__ integer; void* type; } ;
struct acpi_object_list {int count; union acpi_object* pointer; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 void* ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,struct acpi_object_list*,unsigned long long*) ; 

__attribute__((used)) static acpi_status cmpc_set_brightness(acpi_handle handle,
				       unsigned long long value)
{
	union acpi_object param[2];
	struct acpi_object_list input;
	acpi_status status;
	unsigned long long output;

	param[0].type = ACPI_TYPE_INTEGER;
	param[0].integer.value = 0xC0;
	param[1].type = ACPI_TYPE_INTEGER;
	param[1].integer.value = value;
	input.count = 2;
	input.pointer = param;
	status = acpi_evaluate_integer(handle, "GWRI", &input, &output);
	return status;
}