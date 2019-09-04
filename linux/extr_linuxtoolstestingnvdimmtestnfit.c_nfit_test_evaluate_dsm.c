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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  guid_t ;
typedef  int /*<<< orphan*/ * acpi_handle ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 union acpi_object* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfit_ctl_handle ; 
 union acpi_object* result ; 

__attribute__((used)) static union acpi_object *nfit_test_evaluate_dsm(acpi_handle handle,
		const guid_t *guid, u64 rev, u64 func, union acpi_object *argv4)
{
	if (handle != &nfit_ctl_handle)
		return ERR_PTR(-ENXIO);

	return result;
}