#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  value; } ;
struct TYPE_3__ {int length; scalar_t__ pointer; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ u32 ;
struct acpi_buffer {void* member_1; scalar_t__ pointer; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int /*<<< orphan*/  WMID_GUID1 ; 
 int /*<<< orphan*/  kfree (scalar_t__) ; 
 int /*<<< orphan*/  wmi_evaluate_method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,struct acpi_buffer*,struct acpi_buffer*) ; 

__attribute__((used)) static acpi_status
WMI_execute_u32(u32 method_id, u32 in, u32 *out)
{
	struct acpi_buffer input = { (acpi_size) sizeof(u32), (void *)(&in) };
	struct acpi_buffer result = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	u32 tmp = 0;
	acpi_status status;

	status = wmi_evaluate_method(WMID_GUID1, 0, method_id, &input, &result);

	if (ACPI_FAILURE(status))
		return status;

	obj = (union acpi_object *) result.pointer;
	if (obj) {
		if (obj->type == ACPI_TYPE_BUFFER &&
			(obj->buffer.length == sizeof(u32) ||
			obj->buffer.length == sizeof(u64))) {
			tmp = *((u32 *) obj->buffer.pointer);
		} else if (obj->type == ACPI_TYPE_INTEGER) {
			tmp = (u32) obj->integer.value;
		}
	}

	if (out)
		*out = tmp;

	kfree(result.pointer);

	return status;
}