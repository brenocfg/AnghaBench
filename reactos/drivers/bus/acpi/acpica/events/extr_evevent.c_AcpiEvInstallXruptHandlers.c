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
 int /*<<< orphan*/  AcpiEvInitGlobalLockHandler () ; 
 int /*<<< orphan*/  AcpiEvInstallSciHandler () ; 
 int /*<<< orphan*/  AcpiGbl_EventsInitialized ; 
 scalar_t__ AcpiGbl_ReducedHardware ; 
 int /*<<< orphan*/  EvInstallXruptHandlers ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiEvInstallXruptHandlers (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvInstallXruptHandlers);


    /* If Hardware Reduced flag is set, there is no ACPI h/w */

    if (AcpiGbl_ReducedHardware)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* Install the SCI handler */

    Status = AcpiEvInstallSciHandler ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Unable to install System Control Interrupt handler"));
        return_ACPI_STATUS (Status);
    }

    /* Install the handler for the Global Lock */

    Status = AcpiEvInitGlobalLockHandler ();
    if (ACPI_FAILURE (Status))
    {
        ACPI_EXCEPTION ((AE_INFO, Status,
            "Unable to initialize Global Lock handler"));
        return_ACPI_STATUS (Status);
    }

    AcpiGbl_EventsInitialized = TRUE;
    return_ACPI_STATUS (Status);
}