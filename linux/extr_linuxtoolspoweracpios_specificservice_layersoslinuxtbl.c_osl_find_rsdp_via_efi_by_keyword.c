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
typedef  int /*<<< orphan*/  acpi_physical_address ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 int sscanf (char*,char*,unsigned long long*) ; 

__attribute__((used)) static acpi_physical_address
osl_find_rsdp_via_efi_by_keyword(FILE * file, const char *keyword)
{
	char buffer[80];
	unsigned long long address = 0;
	char format[32];

	snprintf(format, 32, "%s=%s", keyword, "%llx");
	fseek(file, 0, SEEK_SET);
	while (fgets(buffer, 80, file)) {
		if (sscanf(buffer, format, &address) == 1) {
			break;
		}
	}

	return ((acpi_physical_address)(address));
}