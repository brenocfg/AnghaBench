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

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_INFO ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiEvTerminate () ; 
 scalar_t__ AcpiGbl_Shutdown ; 
 scalar_t__ AcpiGbl_StartupFlags ; 
 int /*<<< orphan*/  AcpiNsTerminate () ; 
 int /*<<< orphan*/  AcpiTbTerminate () ; 
 int /*<<< orphan*/  AcpiUtDeleteCaches () ; 
 int /*<<< orphan*/  AcpiUtInterfaceTerminate () ; 
 int /*<<< orphan*/  AcpiUtTerminate () ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  UtSubsystemShutdown ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiUtSubsystemShutdown (
    void)
{
    ACPI_FUNCTION_TRACE (UtSubsystemShutdown);


    /* Just exit if subsystem is already shutdown */

    if (AcpiGbl_Shutdown)
    {
        ACPI_ERROR ((AE_INFO, "ACPI Subsystem is already terminated"));
        return_VOID;
    }

    /* Subsystem appears active, go ahead and shut it down */

    AcpiGbl_Shutdown = TRUE;
    AcpiGbl_StartupFlags = 0;
    ACPI_DEBUG_PRINT ((ACPI_DB_INFO, "Shutting down ACPI Subsystem\n"));

#ifndef ACPI_ASL_COMPILER

    /* Close the AcpiEvent Handling */

    AcpiEvTerminate ();

    /* Delete any dynamic _OSI interfaces */

    AcpiUtInterfaceTerminate ();
#endif

    /* Close the Namespace */

    AcpiNsTerminate ();

    /* Delete the ACPI tables */

    AcpiTbTerminate ();

    /* Close the globals */

    AcpiUtTerminate ();

    /* Purge the local caches */

    (void) AcpiUtDeleteCaches ();
    return_VOID;
}