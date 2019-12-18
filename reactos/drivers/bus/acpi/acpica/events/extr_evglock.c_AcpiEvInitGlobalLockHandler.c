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
typedef  scalar_t__ ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EVENT_GLOBAL ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NO_HARDWARE_RESPONSE ; 
 scalar_t__ AE_OK ; 
 int /*<<< orphan*/  AcpiEvGlobalLockHandler ; 
 void* AcpiGbl_GlobalLockPending ; 
 int /*<<< orphan*/  AcpiGbl_GlobalLockPendingLock ; 
 void* AcpiGbl_GlobalLockPresent ; 
 scalar_t__ AcpiGbl_ReducedHardware ; 
 scalar_t__ AcpiInstallFixedEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ AcpiOsCreateLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EvInitGlobalLockHandler ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 

ACPI_STATUS
AcpiEvInitGlobalLockHandler (
    void)
{
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (EvInitGlobalLockHandler);


    /* If Hardware Reduced flag is set, there is no global lock */

    if (AcpiGbl_ReducedHardware)
    {
        return_ACPI_STATUS (AE_OK);
    }

    /* Attempt installation of the global lock handler */

    Status = AcpiInstallFixedEventHandler (ACPI_EVENT_GLOBAL,
        AcpiEvGlobalLockHandler, NULL);

    /*
     * If the global lock does not exist on this platform, the attempt to
     * enable GBL_STATUS will fail (the GBL_ENABLE bit will not stick).
     * Map to AE_OK, but mark global lock as not present. Any attempt to
     * actually use the global lock will be flagged with an error.
     */
    AcpiGbl_GlobalLockPresent = FALSE;
    if (Status == AE_NO_HARDWARE_RESPONSE)
    {
        ACPI_ERROR ((AE_INFO,
            "No response from Global Lock hardware, disabling lock"));

        return_ACPI_STATUS (AE_OK);
    }

    Status = AcpiOsCreateLock (&AcpiGbl_GlobalLockPendingLock);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    AcpiGbl_GlobalLockPending = FALSE;
    AcpiGbl_GlobalLockPresent = TRUE;
    return_ACPI_STATUS (Status);
}