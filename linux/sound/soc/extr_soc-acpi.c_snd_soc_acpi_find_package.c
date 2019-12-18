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
struct TYPE_4__ {scalar_t__ count; } ;
union acpi_object {TYPE_2__ package; } ;
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_acpi_package_context {int data_valid; scalar_t__ length; int /*<<< orphan*/  state; int /*<<< orphan*/  format; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {scalar_t__ functional; scalar_t__ present; } ;
struct acpi_device {TYPE_1__ status; } ;
struct acpi_buffer {union acpi_object* pointer; int /*<<< orphan*/ * member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_BUFFER ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_CTRL_TERMINATE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ acpi_bus_get_device (int /*<<< orphan*/ ,struct acpi_device**) ; 
 int /*<<< orphan*/  acpi_evaluate_object_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct acpi_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_extract_package (union acpi_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 

__attribute__((used)) static acpi_status snd_soc_acpi_find_package(acpi_handle handle, u32 level,
					     void *context, void **ret)
{
	struct acpi_device *adev;
	acpi_status status = AE_OK;
	struct snd_soc_acpi_package_context *pkg_ctx = context;

	pkg_ctx->data_valid = false;

	if (acpi_bus_get_device(handle, &adev))
		return AE_OK;

	if (adev->status.present && adev->status.functional) {
		struct acpi_buffer buffer = {ACPI_ALLOCATE_BUFFER, NULL};
		union acpi_object  *myobj = NULL;

		status = acpi_evaluate_object_typed(handle, pkg_ctx->name,
						NULL, &buffer,
						ACPI_TYPE_PACKAGE);
		if (ACPI_FAILURE(status))
			return AE_OK;

		myobj = buffer.pointer;
		if (!myobj || myobj->package.count != pkg_ctx->length) {
			kfree(buffer.pointer);
			return AE_OK;
		}

		status = acpi_extract_package(myobj,
					pkg_ctx->format, pkg_ctx->state);
		if (ACPI_FAILURE(status)) {
			kfree(buffer.pointer);
			return AE_OK;
		}

		kfree(buffer.pointer);
		pkg_ctx->data_valid = true;
		return AE_CTRL_TERMINATE;
	}

	return AE_OK;
}