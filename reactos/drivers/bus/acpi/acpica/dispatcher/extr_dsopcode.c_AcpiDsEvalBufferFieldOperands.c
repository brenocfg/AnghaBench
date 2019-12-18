#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* Arg; } ;
struct TYPE_12__ {scalar_t__ AmlOpcode; TYPE_1__ Value; int /*<<< orphan*/ * Node; } ;
struct TYPE_14__ {TYPE_2__ Common; } ;
struct TYPE_13__ {int /*<<< orphan*/ ** Operands; } ;
typedef  TYPE_3__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_4__ ACPI_PARSE_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  ACPI_WALK_OPERANDS ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 scalar_t__ AML_CREATE_FIELD_OP ; 
 int /*<<< orphan*/  AcpiDsCreateOperands (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  AcpiDsInitBufferField (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiExResolveOperands (scalar_t__,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * AcpiNsGetAttachedObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiPsGetOpcodeName (scalar_t__) ; 
 int /*<<< orphan*/  DsEvalBufferFieldOperands ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsEvalBufferFieldOperands (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_NAMESPACE_NODE     *Node;
    ACPI_PARSE_OBJECT       *NextOp;


    ACPI_FUNCTION_TRACE_PTR (DsEvalBufferFieldOperands, Op);


    /*
     * This is where we evaluate the address and length fields of the
     * CreateXxxField declaration
     */
    Node =  Op->Common.Node;

    /* NextOp points to the op that holds the Buffer */

    NextOp = Op->Common.Value.Arg;

    /* Evaluate/create the address and length operands */

    Status = AcpiDsCreateOperands (WalkState, NextOp);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (!ObjDesc)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /* Resolve the operands */

    Status = AcpiExResolveOperands (
        Op->Common.AmlOpcode, ACPI_WALK_OPERANDS, WalkState);
    if (ACPI_FAILURE (Status))
    {
        ACPI_ERROR ((AE_INFO, "(%s) bad operand(s), status 0x%X",
            AcpiPsGetOpcodeName (Op->Common.AmlOpcode), Status));

        return_ACPI_STATUS (Status);
    }

    /* Initialize the Buffer Field */

    if (Op->Common.AmlOpcode == AML_CREATE_FIELD_OP)
    {
        /* NOTE: Slightly different operands for this opcode */

        Status = AcpiDsInitBufferField (Op->Common.AmlOpcode, ObjDesc,
            WalkState->Operands[0], WalkState->Operands[1],
            WalkState->Operands[2], WalkState->Operands[3]);
    }
    else
    {
        /* All other, CreateXxxField opcodes */

        Status = AcpiDsInitBufferField (Op->Common.AmlOpcode, ObjDesc,
            WalkState->Operands[0], WalkState->Operands[1],
            NULL, WalkState->Operands[2]);
    }

    return_ACPI_STATUS (Status);
}