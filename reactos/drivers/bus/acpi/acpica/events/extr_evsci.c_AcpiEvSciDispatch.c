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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_3__ {struct TYPE_3__* Next; int /*<<< orphan*/  Context; int /*<<< orphan*/  (* Address ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ ACPI_SCI_HANDLER_INFO ;
typedef  int /*<<< orphan*/  ACPI_CPU_FLAGS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INTERRUPT_NOT_HANDLED ; 
 int /*<<< orphan*/  AcpiGbl_GpeLock ; 
 TYPE_1__* AcpiGbl_SciHandlerList ; 
 int /*<<< orphan*/  AcpiOsAcquireLock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiOsReleaseLock (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EvSciDispatch ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

UINT32
AcpiEvSciDispatch (
    void)
{
    ACPI_SCI_HANDLER_INFO   *SciHandler;
    ACPI_CPU_FLAGS          Flags;
    UINT32                  IntStatus = ACPI_INTERRUPT_NOT_HANDLED;


    ACPI_FUNCTION_NAME (EvSciDispatch);


    /* Are there any host-installed SCI handlers? */

    if (!AcpiGbl_SciHandlerList)
    {
        return (IntStatus);
    }

    Flags = AcpiOsAcquireLock (AcpiGbl_GpeLock);

    /* Invoke all host-installed SCI handlers */

    SciHandler = AcpiGbl_SciHandlerList;
    while (SciHandler)
    {
        /* Invoke the installed handler (at interrupt level) */

        IntStatus |= SciHandler->Address (
            SciHandler->Context);

        SciHandler = SciHandler->Next;
    }

    AcpiOsReleaseLock (AcpiGbl_GpeLock, Flags);
    return (IntStatus);
}