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
struct acpi_buffer {scalar_t__ pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,struct acpi_object_list*,struct acpi_buffer*) ; 
 int /*<<< orphan*/  dprintk (char*,char*,...) ; 
 int /*<<< orphan*/  pr_err (char*,char*) ; 

__attribute__((used)) static union acpi_object *__call_snc_method(acpi_handle handle, char *method,
		u64 *value)
{
	union acpi_object *result = NULL;
	struct acpi_buffer output = { ACPI_ALLOCATE_BUFFER, NULL };
	acpi_status status;

	if (value) {
		struct acpi_object_list params;
		union acpi_object in;
		in.type = ACPI_TYPE_INTEGER;
		in.integer.value = *value;
		params.count = 1;
		params.pointer = &in;
		status = acpi_evaluate_object(handle, method, &params, &output);
		dprintk("__call_snc_method: [%s:0x%.8x%.8x]\n", method,
				(unsigned int)(*value >> 32),
				(unsigned int)*value & 0xffffffff);
	} else {
		status = acpi_evaluate_object(handle, method, NULL, &output);
		dprintk("__call_snc_method: [%s]\n", method);
	}

	if (ACPI_FAILURE(status)) {
		pr_err("Failed to evaluate [%s]\n", method);
		return NULL;
	}

	result = (union acpi_object *) output.pointer;
	if (!result)
		dprintk("No return object [%s]\n", method);

	return result;
}