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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct acpi_table_header {int length; scalar_t__ signature; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_VALIDATE_RSDP_SIG (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  acpi_ut_valid_nameseg (scalar_t__) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  stderr ; 

u8 ap_is_valid_header(struct acpi_table_header *table)
{

	if (!ACPI_VALIDATE_RSDP_SIG(table->signature)) {

		/* Make sure signature is all ASCII and a valid ACPI name */

		if (!acpi_ut_valid_nameseg(table->signature)) {
			fprintf(stderr,
				"Table signature (0x%8.8X) is invalid\n",
				*(u32 *)table->signature);
			return (FALSE);
		}

		/* Check for minimum table length */

		if (table->length < sizeof(struct acpi_table_header)) {
			fprintf(stderr, "Table length (0x%8.8X) is invalid\n",
				table->length);
			return (FALSE);
		}
	}

	return (TRUE);
}