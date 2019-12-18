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
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvFixedEventInitialize () ; 
 int /*<<< orphan*/  AcpiEvGpeInitialize () ; 
 scalar_t__ AcpiGbl_ReducedHardware ; 
 int /*<<< orphan*/  EvInitializeEvents ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvInitializeEvents (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvInitializeEvents);


    /* If Hardware Reduced flag is set, there are no fixed events */

    if (AcpiGbl_ReducedHardware)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /*
     * Initialize the Fixed and General Purpose Events. This is done prior to
     * enabling SCIs to prevent interrupts from occurring before the handlers
     * are installed.
     */
    Status = AcpiEvFixedEventInitialize ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Unable to initialize fixed events"));
        return_ACPI_STATUS (Status);
    }

    Status = AcpiEvGpeInitialize ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Unable to initialize general purpose events"));
        return_ACPI_STATUS (Status);
    }

    return_ACPI_STATUS (Status);
}