#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int Flags; struct TYPE_4__* Name; struct TYPE_4__* Next; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_INTERFACE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 int ACPI_OSI_DEFAULT_INVALID ; 
 int ACPI_OSI_DYNAMIC ; 
 int ACPI_OSI_INVALID ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGbl_OsiMutex ; 
 TYPE_1__* AcpiGbl_SupportedInterfaces ; 
 int /*<<< orphan*/  AcpiOsAcquireMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtInterfaceTerminate (
    void)
{
    ACPI_STATUS             Status;
    ACPI_INTERFACE_INFO     *NextInterface;


    Status = AcpiOsAcquireMutex (AcpiGbl_OsiMutex, ACPI_WAIT_FOREVER);
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    NextInterface = AcpiGbl_SupportedInterfaces;
    while (NextInterface)
    {
        AcpiGbl_SupportedInterfaces = NextInterface->Next;

        if (NextInterface->Flags & ACPI_OSI_DYNAMIC)
        {
            /* Only interfaces added at runtime can be freed */

            ACPI_FREE (NextInterface->Name);
            ACPI_FREE (NextInterface);
        }
        else
        {
            /* Interface is in static list. Reset it to invalid or valid. */

            if (NextInterface->Flags & ACPI_OSI_DEFAULT_INVALID)
            {
                NextInterface->Flags |= ACPI_OSI_INVALID;
            }
            else
            {
                NextInterface->Flags &= ~ACPI_OSI_INVALID;
            }
        }

        NextInterface = AcpiGbl_SupportedInterfaces;
    }

    AcpiOsReleaseMutex (AcpiGbl_OsiMutex);
    return (AE_OK);
}