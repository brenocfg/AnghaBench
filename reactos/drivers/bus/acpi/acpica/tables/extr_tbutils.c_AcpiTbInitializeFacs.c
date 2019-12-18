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
struct TYPE_2__ {scalar_t__ Facs; scalar_t__ XFacs; } ;
typedef  int /*<<< orphan*/  ACPI_TABLE_FACS ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CAST_INDIRECT_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  ACPI_TABLE_HEADER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/ * AcpiGbl_FACS ; 
 TYPE_1__ AcpiGbl_FADT ; 
 int /*<<< orphan*/  AcpiGbl_FacsIndex ; 
 scalar_t__ AcpiGbl_ReducedHardware ; 
 int /*<<< orphan*/  AcpiGbl_Use32BitFacsAddresses ; 
 int /*<<< orphan*/  AcpiGbl_XFacsIndex ; 
 int /*<<< orphan*/  AcpiGetTableByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiTbInitializeFacs (
    void)
{
    ACPI_TABLE_FACS         *Facs;


    /* If Hardware Reduced flag is set, there is no FACS */

    if (AcpiGbl_ReducedHardware)
    {
        AcpiGbl_FACS = NULL;
        return (AE_OK);
    }
    else if (AcpiGbl_FADT.XFacs &&
         (!AcpiGbl_FADT.Facs || !AcpiGbl_Use32BitFacsAddresses))
    {
        (void) AcpiGetTableByIndex (AcpiGbl_XFacsIndex,
            ACPI_CAST_INDIRECT_PTR (ACPI_TABLE_HEADER, &Facs));
        AcpiGbl_FACS = Facs;
    }
    else if (AcpiGbl_FADT.Facs)
    {
        (void) AcpiGetTableByIndex (AcpiGbl_FacsIndex,
            ACPI_CAST_INDIRECT_PTR (ACPI_TABLE_HEADER, &Facs));
        AcpiGbl_FACS = Facs;
    }

    /* If there is no FACS, just continue. There was already an error msg */

    return (AE_OK);
}