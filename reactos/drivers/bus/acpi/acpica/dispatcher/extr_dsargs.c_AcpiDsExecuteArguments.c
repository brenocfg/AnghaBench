#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_11__ {int /*<<< orphan*/ * Node; } ;
struct TYPE_13__ {TYPE_1__ Common; } ;
struct TYPE_12__ {int /*<<< orphan*/ * DeferredNode; int /*<<< orphan*/  ParseFlags; } ;
typedef  TYPE_2__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ACPI_IMODE_EXECUTE ; 
 int /*<<< orphan*/  ACPI_IMODE_LOAD_PASS1 ; 
 int /*<<< orphan*/  ACPI_PARSE_DEFERRED_OP ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AML_INT_EVAL_SUBTREE_OP ; 
 TYPE_2__* AcpiDsCreateWalkState (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiDsDeleteWalkState (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiDsInitAmlWalk (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* AcpiPsAllocOp (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiPsDeleteParseTree (TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiPsParseAml (TYPE_2__*) ; 
 int /*<<< orphan*/  DsExecuteArguments ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiDsExecuteArguments (
    ACPI_NAMESPACE_NODE     *Node,
    ACPI_NAMESPACE_NODE     *ScopeNode,
    UINT32                  AmlLength,
    UINT8                   *AmlStart)
{
    ACPI_STATUS             Status;
    ACPI_PARSE_OBJECT       *Op;
    ACPI_WALK_STATE         *WalkState;


    ACPI_FUNCTION_TRACE_PTR (DsExecuteArguments, AmlStart);


    /* Allocate a new parser op to be the root of the parsed tree */

    Op = AcpiPsAllocOp (AML_INT_EVAL_SUBTREE_OP, AmlStart);
    if (!Op)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Save the Node for use in AcpiPsParseAml */

    Op->Common.Node = ScopeNode;

    /* Create and initialize a new parser state */

    WalkState = AcpiDsCreateWalkState (0, NULL, NULL, NULL);
    if (!WalkState)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    Status = AcpiDsInitAmlWalk (WalkState, Op, NULL, AmlStart,
        AmlLength, NULL, ACPI_IMODE_LOAD_PASS1);
    if (ACPI_FAILURE (Status))
    {
        AcpiDsDeleteWalkState (WalkState);
        goto Cleanup;
    }

    /* Mark this parse as a deferred opcode */

    WalkState->ParseFlags = ACPI_PARSE_DEFERRED_OP;
    WalkState->DeferredNode = Node;

    /* Pass1: Parse the entire declaration */

    Status = AcpiPsParseAml (WalkState);
    if (ACPI_FAILURE (Status))
    {
        goto Cleanup;
    }

    /* Get and init the Op created above */

    Op->Common.Node = Node;
    AcpiPsDeleteParseTree (Op);

    /* Evaluate the deferred arguments */

    Op = AcpiPsAllocOp (AML_INT_EVAL_SUBTREE_OP, AmlStart);
    if (!Op)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    Op->Common.Node = ScopeNode;

    /* Create and initialize a new parser state */

    WalkState = AcpiDsCreateWalkState (0, NULL, NULL, NULL);
    if (!WalkState)
    {
        Status = AE_NO_MEMORY;
        goto Cleanup;
    }

    /* Execute the opcode and arguments */

    Status = AcpiDsInitAmlWalk (WalkState, Op, NULL, AmlStart,
        AmlLength, NULL, ACPI_IMODE_EXECUTE);
    if (ACPI_FAILURE (Status))
    {
        AcpiDsDeleteWalkState (WalkState);
        goto Cleanup;
    }

    /* Mark this execution as a deferred opcode */

    WalkState->DeferredNode = Node;
    Status = AcpiPsParseAml (WalkState);

Cleanup:
    AcpiPsDeleteParseTree (Op);
    return_ACPI_STATUS (Status);
}