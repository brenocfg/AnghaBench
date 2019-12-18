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
typedef  int /*<<< orphan*/  ACPI_TABLE_DESC ;

/* Variables and functions */
 int /*<<< orphan*/  AcpiTbInvalidateTable (int /*<<< orphan*/ *) ; 

void
AcpiTbReleaseTempTable (
    ACPI_TABLE_DESC         *TableDesc)
{

    /*
     * Note that the .Address is maintained by the callers of
     * AcpiTbAcquireTempTable(), thus do not invoke AcpiTbUninstallTable()
     * where .Address will be freed.
     */
    AcpiTbInvalidateTable (TableDesc);
}