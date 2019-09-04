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
struct TYPE_2__ {unsigned long long value; } ;
union acpi_object {TYPE_1__ integer; } ;
typedef  enum intel_hid_dsm_fn_codes { ____Placeholder_intel_hid_dsm_fn_codes } intel_hid_dsm_fn_codes ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FREE (union acpi_object*) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int INTEL_HID_DSM_FN_INVALID ; 
 int INTEL_HID_DSM_FN_MAX ; 
 union acpi_object* acpi_evaluate_dsm_typed (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  acpi_handle_debug (int /*<<< orphan*/ ,char*,int,char*,unsigned long long) ; 
 int /*<<< orphan*/  intel_dsm_guid ; 
 int intel_hid_dsm_fn_mask ; 
 scalar_t__* intel_hid_dsm_fn_to_method ; 

__attribute__((used)) static bool intel_hid_evaluate_method(acpi_handle handle,
				      enum intel_hid_dsm_fn_codes fn_index,
				      unsigned long long *result)
{
	union acpi_object *obj;
	acpi_status status;
	char *method_name;

	if (fn_index <= INTEL_HID_DSM_FN_INVALID ||
	    fn_index >= INTEL_HID_DSM_FN_MAX)
		return false;

	method_name = (char *)intel_hid_dsm_fn_to_method[fn_index];

	if (!(intel_hid_dsm_fn_mask & fn_index))
		goto skip_dsm_eval;

	obj = acpi_evaluate_dsm_typed(handle, &intel_dsm_guid,
				      1, fn_index,
				      NULL,  ACPI_TYPE_INTEGER);
	if (obj) {
		*result = obj->integer.value;
		acpi_handle_debug(handle,
				  "Eval DSM Fn code: %d[%s] results: 0x%llx\n",
				  fn_index, method_name, *result);
		ACPI_FREE(obj);
		return true;
	}

skip_dsm_eval:
	status = acpi_evaluate_integer(handle, method_name, NULL, result);
	if (ACPI_SUCCESS(status))
		return true;

	return false;
}