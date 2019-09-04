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
struct TYPE_2__ {int /*<<< orphan*/ * pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 int /*<<< orphan*/  ACPI_TYPE_BUFFER ; 
 int /*<<< orphan*/  HID_EVENT_FILTER_UUID ; 
 union acpi_object* acpi_evaluate_dsm_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  guid_parse (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intel_dsm_guid ; 
 int /*<<< orphan*/  intel_hid_dsm_fn_mask ; 

__attribute__((used)) static void intel_hid_init_dsm(acpi_handle handle)
{
	union acpi_object *obj;

	guid_parse(HID_EVENT_FILTER_UUID, &intel_dsm_guid);

	obj = acpi_evaluate_dsm_typed(handle, &intel_dsm_guid, 1, 0, NULL,
				      ACPI_TYPE_BUFFER);
	if (obj) {
		intel_hid_dsm_fn_mask = *obj->buffer.pointer;
		ACPI_FREE(obj);
	}

	acpi_handle_debug(handle, "intel_hid_dsm_fn_mask = %llx\n",
			  intel_hid_dsm_fn_mask);
}