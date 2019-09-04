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
struct TYPE_4__ {scalar_t__ value; } ;
struct TYPE_3__ {int count; union acpi_object* elements; } ;
union acpi_object {scalar_t__ type; TYPE_2__ integer; TYPE_1__ package; } ;
typedef  size_t u32 ;
struct ath10k {int dummy; } ;

/* Variables and functions */
 scalar_t__ ACPI_TYPE_INTEGER ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 scalar_t__ WRDD_WIFI ; 
 int /*<<< orphan*/  ath10k_warn (struct ath10k*,char*) ; 

__attribute__((used)) static u32 ath10k_mac_wrdd_get_mcc(struct ath10k *ar, union acpi_object *wrdd)
{
	union acpi_object *mcc_pkg;
	union acpi_object *domain_type;
	union acpi_object *mcc_value;
	u32 i;

	if (wrdd->type != ACPI_TYPE_PACKAGE ||
	    wrdd->package.count < 2 ||
	    wrdd->package.elements[0].type != ACPI_TYPE_INTEGER ||
	    wrdd->package.elements[0].integer.value != 0) {
		ath10k_warn(ar, "ignoring malformed/unsupported wrdd structure\n");
		return 0;
	}

	for (i = 1; i < wrdd->package.count; ++i) {
		mcc_pkg = &wrdd->package.elements[i];

		if (mcc_pkg->type != ACPI_TYPE_PACKAGE)
			continue;
		if (mcc_pkg->package.count < 2)
			continue;
		if (mcc_pkg->package.elements[0].type != ACPI_TYPE_INTEGER ||
		    mcc_pkg->package.elements[1].type != ACPI_TYPE_INTEGER)
			continue;

		domain_type = &mcc_pkg->package.elements[0];
		if (domain_type->integer.value != WRDD_WIFI)
			continue;

		mcc_value = &mcc_pkg->package.elements[1];
		return mcc_value->integer.value;
	}
	return 0;
}