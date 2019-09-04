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
struct TYPE_3__ {int length; scalar_t__ pointer; } ;
union acpi_object {scalar_t__ type; TYPE_1__ buffer; } ;
typedef  int uint32_t ;
struct TYPE_4__ {scalar_t__ type; } ;
struct acpi_madt_local_apic {int lapic_flags; scalar_t__ id; TYPE_2__ header; } ;
struct acpi_buffer {union acpi_object* pointer; scalar_t__ length; int /*<<< orphan*/ * member_1; scalar_t__ member_0; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int ACPI_MADT_ENABLED ; 
 scalar_t__ ACPI_MADT_TYPE_LOCAL_APIC ; 
 scalar_t__ ACPI_TYPE_BUFFER ; 
 int EINVAL ; 
 int /*<<< orphan*/  acpi_evaluate_object (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,struct acpi_buffer*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static int xen_apic_id(acpi_handle handle)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	union acpi_object *obj;
	struct acpi_madt_local_apic *lapic;
	int apic_id;

	if (ACPI_FAILURE(acpi_evaluate_object(handle, "_MAT", NULL, &buffer)))
		return -EINVAL;

	if (!buffer.length || !buffer.pointer)
		return -EINVAL;

	obj = buffer.pointer;
	if (obj->type != ACPI_TYPE_BUFFER ||
	    obj->buffer.length < sizeof(*lapic)) {
		kfree(buffer.pointer);
		return -EINVAL;
	}

	lapic = (struct acpi_madt_local_apic *)obj->buffer.pointer;

	if (lapic->header.type != ACPI_MADT_TYPE_LOCAL_APIC ||
	    !(lapic->lapic_flags & ACPI_MADT_ENABLED)) {
		kfree(buffer.pointer);
		return -EINVAL;
	}

	apic_id = (uint32_t)lapic->id;
	kfree(buffer.pointer);
	buffer.length = ACPI_ALLOCATE_BUFFER;
	buffer.pointer = NULL;

	return apic_id;
}