#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * StartOp; } ;
struct TYPE_9__ {TYPE_1__ ParserState; int /*<<< orphan*/ * Thread; int /*<<< orphan*/ * Origin; int /*<<< orphan*/  OwnerId; int /*<<< orphan*/ * MethodDesc; int /*<<< orphan*/  DescriptorType; } ;
typedef  TYPE_2__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_THREAD_STATE ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OWNER_ID ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 TYPE_2__* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_WALK ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDsMethodDataInit (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiDsPushWalkState (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsCreateWalkState ; 
 int /*<<< orphan*/  return_PTR (TYPE_2__*) ; 

ACPI_WALK_STATE *
AcpiDsCreateWalkState (
    ACPI_OWNER_ID           OwnerId,
    ACPI_PARSE_OBJECT       *Origin,
    ACPI_OPERAND_OBJECT     *MethodDesc,
    ACPI_THREAD_STATE       *Thread)
{
    ACPI_WALK_STATE         *WalkState;


    ACPI_FUNCTION_TRACE (DsCreateWalkState);


    WalkState = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_WALK_STATE));
    if (!WalkState)
    {
        return_PTR (NULL);
    }

    WalkState->DescriptorType = ACPI_DESC_TYPE_WALK;
    WalkState->MethodDesc = MethodDesc;
    WalkState->OwnerId = OwnerId;
    WalkState->Origin = Origin;
    WalkState->Thread = Thread;

    WalkState->ParserState.StartOp = Origin;

    /* Init the method args/local */

#ifndef ACPI_CONSTANT_EVAL_ONLY
    AcpiDsMethodDataInit (WalkState);
#endif

    /* Put the new state at the head of the walk list */

    if (Thread)
    {
        AcpiDsPushWalkState (WalkState, Thread);
    }

    return_PTR (WalkState);
}