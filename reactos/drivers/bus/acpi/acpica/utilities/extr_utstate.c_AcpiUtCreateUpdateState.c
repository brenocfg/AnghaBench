#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT16 ;
struct TYPE_7__ {int /*<<< orphan*/  Value; int /*<<< orphan*/ * Object; } ;
struct TYPE_6__ {int /*<<< orphan*/  DescriptorType; } ;
struct TYPE_8__ {TYPE_2__ Update; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  TYPE_3__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DESC_TYPE_STATE_UPDATE ; 
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 TYPE_3__* AcpiUtCreateGenericState () ; 

ACPI_GENERIC_STATE *
AcpiUtCreateUpdateState (
    ACPI_OPERAND_OBJECT     *Object,
    UINT16                  Action)
{
    ACPI_GENERIC_STATE      *State;


    ACPI_FUNCTION_ENTRY ();


    /* Create the generic state object */

    State = AcpiUtCreateGenericState ();
    if (!State)
    {
        return (NULL);
    }

    /* Init fields specific to the update struct */

    State->Common.DescriptorType = ACPI_DESC_TYPE_STATE_UPDATE;
    State->Update.Object = Object;
    State->Update.Value = Action;
    return (State);
}