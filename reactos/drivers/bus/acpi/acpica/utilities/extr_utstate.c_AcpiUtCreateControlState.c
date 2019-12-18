#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  State; int /*<<< orphan*/  DescriptorType; } ;
struct TYPE_6__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CONTROL_CONDITIONAL_EXECUTING ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_CONTROL ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 TYPE_2__* AcpiUtCreateGenericState () ; 

ACPI_GENERIC_STATE *
AcpiUtCreateControlState (
    void)
{
    ACPI_GENERIC_STATE      *State;


    ACPI_FUNCTION_ENTRY ();


    /* Create the generic state object */

    State = AcpiUtCreateGenericState ();
    if (!State)
    {
        return (NULL);
    }

    /* Init fields specific to the control struct */

    State->Common.DescriptorType = ACPI_DESC_TYPE_STATE_CONTROL;
    State->Common.State = ACPI_CONTROL_CONDITIONAL_EXECUTING;

    return (State);
}