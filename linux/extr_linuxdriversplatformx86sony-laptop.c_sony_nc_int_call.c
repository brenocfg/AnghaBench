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
typedef  int u64 ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 int EINVAL ; 
 union acpi_object* __call_snc_method (int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  pr_warn (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sony_nc_int_call(acpi_handle handle, char *name, int *value,
		int *result)
{
	union acpi_object *object = NULL;
	if (value) {
		u64 v = *value;
		object = __call_snc_method(handle, name, &v);
	} else
		object = __call_snc_method(handle, name, NULL);

	if (!object)
		return -EINVAL;

	if (object->type != ACPI_TYPE_INTEGER) {
		pr_warn("Invalid acpi_object: expected 0x%x got 0x%x\n",
				ACPI_TYPE_INTEGER, object->type);
		kfree(object);
		return -EINVAL;
	}

	if (result)
		*result = object->integer.value;

	kfree(object);
	return 0;
}