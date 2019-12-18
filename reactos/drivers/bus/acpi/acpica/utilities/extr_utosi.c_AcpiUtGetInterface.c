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
struct TYPE_4__ {struct TYPE_4__* Next; int /*<<< orphan*/  Name; } ;
typedef  int /*<<< orphan*/  ACPI_STRING ;
typedef  TYPE_1__ ACPI_INTERFACE_INFO ;

/* Variables and functions */
 TYPE_1__* AcpiGbl_SupportedInterfaces ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ACPI_INTERFACE_INFO *
AcpiUtGetInterface (
    ACPI_STRING             InterfaceName)
{
    ACPI_INTERFACE_INFO     *NextInterface;


    NextInterface = AcpiGbl_SupportedInterfaces;
    while (NextInterface)
    {
        if (!strcmp (InterfaceName, NextInterface->Name))
        {
            return (NextInterface);
        }

        NextInterface = NextInterface->Next;
    }

    return (NULL);
}