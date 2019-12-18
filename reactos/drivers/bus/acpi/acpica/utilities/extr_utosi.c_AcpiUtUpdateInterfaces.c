#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT8 ;
struct TYPE_3__ {int Flags; struct TYPE_3__* Next; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_1__ ACPI_INTERFACE_INFO ;

/* Variables and functions */
 int ACPI_DISABLE_INTERFACES ; 
 int ACPI_FEATURE_STRINGS ; 
 int ACPI_OSI_FEATURE ; 
 int ACPI_OSI_INVALID ; 
 int ACPI_VENDOR_STRINGS ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* AcpiGbl_SupportedInterfaces ; 

ACPI_STATUS
AcpiUtUpdateInterfaces (
    UINT8                   Action)
{
    ACPI_INTERFACE_INFO     *NextInterface;


    NextInterface = AcpiGbl_SupportedInterfaces;
    while (NextInterface)
    {
        if (((NextInterface->Flags & ACPI_OSI_FEATURE) &&
             (Action & ACPI_FEATURE_STRINGS)) ||
            (!(NextInterface->Flags & ACPI_OSI_FEATURE) &&
             (Action & ACPI_VENDOR_STRINGS)))
        {
            if (Action & ACPI_DISABLE_INTERFACES)
            {
                /* Mark the interfaces as invalid */

                NextInterface->Flags |= ACPI_OSI_INVALID;
            }
            else
            {
                /* Mark the interfaces as valid */

                NextInterface->Flags &= ~ACPI_OSI_INVALID;
            }
        }

        NextInterface = NextInterface->Next;
    }

    return (AE_OK);
}