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
union acpi_object {scalar_t__ type; TYPE_1__ integer; } ;
struct asus_laptop {int /*<<< orphan*/  handle; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int EIO ; 
 int /*<<< orphan*/  METHOD_PEGA_READ ; 
 int write_acpi_int_ret (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct acpi_buffer*) ; 

__attribute__((used)) static int pega_int_read(struct asus_laptop *asus, int arg, int *result)
{
	struct acpi_buffer buffer = { ACPI_ALLOCATE_BUFFER, NULL };
	int err = write_acpi_int_ret(asus->handle, METHOD_PEGA_READ, arg,
				     &buffer);
	if (!err) {
		union acpi_object *obj = buffer.pointer;
		if (obj && obj->type == ACPI_TYPE_INTEGER)
			*result = obj->integer.value;
		else
			err = -EIO;
	}
	return err;
}