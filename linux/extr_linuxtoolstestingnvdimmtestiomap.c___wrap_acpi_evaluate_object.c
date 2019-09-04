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
typedef  union acpi_object {int dummy; } acpi_object ;
struct nfit_test_resource {union acpi_object** buf; } ;
struct acpi_object_list {int dummy; } ;
struct acpi_buffer {int length; union acpi_object* pointer; } ;
typedef  int /*<<< orphan*/  acpi_string ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_evaluate_object (scalar_t__,int /*<<< orphan*/ ,struct acpi_object_list*,struct acpi_buffer*) ; 
 struct nfit_test_resource* get_nfit_res (long) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

acpi_status __wrap_acpi_evaluate_object(acpi_handle handle, acpi_string path,
		struct acpi_object_list *p, struct acpi_buffer *buf)
{
	struct nfit_test_resource *nfit_res = get_nfit_res((long) handle);
	union acpi_object **obj;

	if (!nfit_res || strcmp(path, "_FIT") || !buf)
		return acpi_evaluate_object(handle, path, p, buf);

	obj = nfit_res->buf;
	buf->length = sizeof(union acpi_object);
	buf->pointer = *obj;
	return AE_OK;
}