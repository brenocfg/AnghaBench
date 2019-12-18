#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ Scope; } ;
struct TYPE_9__ {TYPE_3__* Next; } ;
struct TYPE_11__ {TYPE_1__ Common; } ;
struct TYPE_10__ {scalar_t__ DescriptorType; TYPE_3__* Results; TYPE_3__* ScopeInfo; TYPE_3__* ControlState; TYPE_5__ ParserState; } ;
typedef  TYPE_2__ ACPI_WALK_STATE ;
typedef  TYPE_3__ ACPI_GENERIC_STATE ;

/* Variables and functions */
 scalar_t__ ACPI_DESC_TYPE_WALK ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_2__*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AcpiPsCleanupScope (TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiUtDeleteGenericState (TYPE_3__*) ; 
 int /*<<< orphan*/  DsDeleteWalkState ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiDsDeleteWalkState (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_GENERIC_STATE      *State;


    ACPI_FUNCTION_TRACE_PTR (DsDeleteWalkState, WalkState);


    if (!WalkState)
    {
        return_VOID;
    }

    if (WalkState->DescriptorType != ACPI_DESC_TYPE_WALK)
    {
        ACPI_ERROR ((AE_INFO, "%p is not a valid walk state",
            WalkState));
        return_VOID;
    }

    /* There should not be any open scopes */

    if (WalkState->ParserState.Scope)
    {
        ACPI_ERROR ((AE_INFO, "%p walk still has a scope list",
            WalkState));
        AcpiPsCleanupScope (&WalkState->ParserState);
    }

    /* Always must free any linked control states */

    while (WalkState->ControlState)
    {
        State = WalkState->ControlState;
        WalkState->ControlState = State->Common.Next;

        AcpiUtDeleteGenericState (State);
    }

    /* Always must free any linked parse states */

    while (WalkState->ScopeInfo)
    {
        State = WalkState->ScopeInfo;
        WalkState->ScopeInfo = State->Common.Next;

        AcpiUtDeleteGenericState (State);
    }

    /* Always must free any stacked result states */

    while (WalkState->Results)
    {
        State = WalkState->Results;
        WalkState->Results = State->Common.Next;

        AcpiUtDeleteGenericState (State);
    }

    ACPI_FREE (WalkState);
    return_VOID;
}