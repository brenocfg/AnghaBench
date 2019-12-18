#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_33__ {int /*<<< orphan*/ ** Parameters; } ;
struct TYPE_27__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_32__ {TYPE_1__ Name; } ;
struct TYPE_28__ {scalar_t__ (* Implementation ) (TYPE_4__*) ;} ;
struct TYPE_29__ {size_t ParamCount; int InfoFlags; TYPE_2__ Dispatch; int /*<<< orphan*/  AmlLength; int /*<<< orphan*/  AmlStart; int /*<<< orphan*/  OwnerId; } ;
struct TYPE_31__ {TYPE_3__ Method; } ;
struct TYPE_30__ {size_t NumOperands; int MethodNestingDepth; int /*<<< orphan*/ * MethodPathname; int /*<<< orphan*/  MethodIsNested; int /*<<< orphan*/ ** Operands; TYPE_6__* MethodCallNode; int /*<<< orphan*/  PrevOp; } ;
typedef  TYPE_4__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_THREAD_STATE ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_PARSE_OBJECT ;
typedef  TYPE_5__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_6__ ACPI_NAMESPACE_NODE ;
typedef  TYPE_7__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 TYPE_7__* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DB_EVALUATION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT_RAW (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_7__*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int ACPI_METHOD_INTERNAL_ONLY ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 scalar_t__ AE_NO_MEMORY ; 
 scalar_t__ AE_NULL_ENTRY ; 
 scalar_t__ AE_NULL_OBJECT ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiDsBeginMethodExecution (TYPE_6__*,TYPE_5__*,TYPE_4__*) ; 
 TYPE_4__* AcpiDsCreateWalkState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDsDeleteWalkState (TYPE_4__*) ; 
 scalar_t__ AcpiDsInitAmlWalk (TYPE_4__*,int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiDsTerminateControlMethod (TYPE_5__*,TYPE_4__*) ; 
 TYPE_5__* AcpiNsGetAttachedObject (TYPE_6__*) ; 
 int /*<<< orphan*/ * AcpiNsGetNormalizedPathname (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsCallControlMethod ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 scalar_t__ stub1 (TYPE_4__*) ; 

ACPI_STATUS
AcpiDsCallControlMethod (
    ACPI_THREAD_STATE       *Thread,
    ACPI_WALK_STATE         *ThisWalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *MethodNode;
    ACPI_WALK_STATE         *NextWalkState = NULL;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_EVALUATE_INFO      *Info;
    UINT32                  i;


    ACPI_FUNCTION_TRACE_PTR (DsCallControlMethod, ThisWalkState);

    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
        "Calling method %p, currentstate=%p\n",
        ThisWalkState->PrevOp, ThisWalkState));

    /*
     * Get the namespace entry for the control method we are about to call
     */
    MethodNode = ThisWalkState->MethodCallNode;
    if (!MethodNode)
    {
        return_ACPI_STATUS (AE_NULL_ENTRY);
    }

    ObjDesc = AcpiNsGetAttachedObject (MethodNode);
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NULL_OBJECT);
    }

    /* Init for new method, possibly wait on method mutex */

    Status = AcpiDsBeginMethodExecution (
        MethodNode, ObjDesc, ThisWalkState);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Begin method parse/execution. Create a new walk state */

    NextWalkState = AcpiDsCreateWalkState (
        ObjDesc->Method.OwnerId, NULL, ObjDesc, Thread);
    if (!NextWalkState)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /*
     * The resolved arguments were put on the previous walk state's operand
     * stack. Operands on the previous walk state stack always
     * start at index 0. Also, null terminate the list of arguments
     */
    ThisWalkState->Operands [ThisWalkState->NumOperands] = NULL;

    /*
     * Allocate and initialize the evaluation information block
     * TBD: this is somewhat inefficient, should change interface to
     * DsInitAmlWalk. For now, keeps this struct off the CPU stack
     */
    Info = ACPI_ALLOCATE_ZEROED (sizeof (ACPI_EVALUATE_INFO));
    if (!Info)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    Info->Parameters = &ThisWalkState->Operands[0];

    Status = AcpiDsInitAmlWalk (NextWalkState, NULL, MethodNode,
        ObjDesc->Method.AmlStart, ObjDesc->Method.AmlLength,
        Info, ACPI_IMODE_EXECUTE);

    ACPI_FREE (Info);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    NextWalkState->MethodNestingDepth = ThisWalkState->MethodNestingDepth + 1;

    /*
     * Delete the operands on the previous walkstate operand stack
     * (they were copied to new objects)
     */
    for (i = 0; i < ObjDesc->Method.ParamCount; i++)
    {
        AcpiUtRemoveReference (ThisWalkState->Operands [i]);
        ThisWalkState->Operands [i] = NULL;
    }

    /* Clear the operand stack */

    ThisWalkState->NumOperands = 0;

    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
        "**** Begin nested execution of [%4.4s] **** WalkState=%p\n",
        MethodNode->Name.Ascii, NextWalkState));

    ThisWalkState->MethodPathname = AcpiNsGetNormalizedPathname (MethodNode, TRUE);
    ThisWalkState->MethodIsNested = TRUE;

    /* Optional object evaluation log */

    ACPI_DEBUG_PRINT_RAW ((ACPI_DB_EVALUATION,
        "%-26s:  %*s%s\n", "   Nested method call",
        NextWalkState->MethodNestingDepth * 3, " ",
        &ThisWalkState->MethodPathname[1]));

    /* Invoke an internal method if necessary */

    if (ObjDesc->Method.InfoFlags & ACPI_METHOD_INTERNAL_ONLY)
    {
        Status = ObjDesc->Method.Dispatch.Implementation (NextWalkState);
        if (Status == AE_OK)
        {
            Status = AE_CTRL_TERMINATE;
        }
    }

    return_ACPI_STATUS (Status);


Cleanup:

    /* On error, we must terminate the method properly */

    AcpiDsTerminateControlMethod (ObjDesc, NextWalkState);
    AcpiDsDeleteWalkState (NextWalkState);

    return_ACPI_STATUS (Status);
}