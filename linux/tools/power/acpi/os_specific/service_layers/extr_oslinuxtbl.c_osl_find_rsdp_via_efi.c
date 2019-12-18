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
typedef  scalar_t__ acpi_physical_address ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  EFI_SYSTAB ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ osl_find_rsdp_via_efi_by_keyword (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static acpi_physical_address osl_find_rsdp_via_efi(void)
{
	FILE *file;
	acpi_physical_address address = 0;

	file = fopen(EFI_SYSTAB, "r");
	if (file) {
		address = osl_find_rsdp_via_efi_by_keyword(file, "ACPI20");
		if (!address) {
			address =
			    osl_find_rsdp_via_efi_by_keyword(file, "ACPI");
		}
		fclose(file);
	}

	return (address);
}