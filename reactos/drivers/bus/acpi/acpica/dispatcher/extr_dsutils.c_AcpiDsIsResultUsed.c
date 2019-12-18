#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_23__ {int Class; } ;
struct TYPE_20__ {scalar_t__ AmlOpcode; TYPE_5__* Parent; } ;
struct TYPE_22__ {TYPE_6__ Common; } ;
struct TYPE_21__ {TYPE_3__* ControlState; int /*<<< orphan*/  ResultObj; } ;
struct TYPE_18__ {scalar_t__ AmlOpcode; } ;
struct TYPE_19__ {TYPE_4__ Common; } ;
struct TYPE_16__ {TYPE_8__* PredicateOp; } ;
struct TYPE_15__ {int /*<<< orphan*/  State; } ;
struct TYPE_17__ {TYPE_2__ Control; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;
typedef  TYPE_7__ ACPI_WALK_STATE ;
typedef  TYPE_8__ ACPI_PARSE_OBJECT ;
typedef  TYPE_9__ ACPI_OPCODE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_CONTROL_PREDICATE_EXECUTING ; 
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AML_BANK_FIELD_OP ; 
 scalar_t__ AML_BUFFER_OP ; 
#define  AML_CLASS_CONTROL 133 
#define  AML_CLASS_CREATE 132 
#define  AML_CLASS_NAMED_OBJECT 131 
 int AML_CLASS_UNKNOWN ; 
 scalar_t__ AML_DATA_REGION_OP ; 
#define  AML_IF_OP 130 
 scalar_t__ AML_INT_EVAL_SUBTREE_OP ; 
 scalar_t__ AML_PACKAGE_OP ; 
 scalar_t__ AML_REGION_OP ; 
#define  AML_RETURN_OP 129 
 scalar_t__ AML_SCOPE_OP ; 
 scalar_t__ AML_VARIABLE_PACKAGE_OP ; 
#define  AML_WHILE_OP 128 
 int /*<<< orphan*/  AcpiDsDoImplicitReturn (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ) ; 
 TYPE_9__* AcpiPsGetOpcodeInfo (scalar_t__) ; 
 int /*<<< orphan*/  AcpiPsGetOpcodeName (scalar_t__) ; 
 int /*<<< orphan*/  DsIsResultUsed ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  return_UINT8 (int /*<<< orphan*/ ) ; 

BOOLEAN
AcpiDsIsResultUsed (
    ACPI_PARSE_OBJECT       *Op,
    ACPI_WALK_STATE         *WalkState)
{
    const ACPI_OPCODE_INFO  *ParentInfo;

    ACPI_FUNCTION_TRACE_PTR (DsIsResultUsed, Op);


    /* Must have both an Op and a Result Object */

    if (!Op)
    {
        ACPI_ERROR ((AE_INFO, "Null Op"));
        return_UINT8 (TRUE);
    }

    /*
     * We know that this operator is not a
     * Return() operator (would not come here.) The following code is the
     * optional support for a so-called "implicit return". Some AML code
     * assumes that the last value of the method is "implicitly" returned
     * to the caller. Just save the last result as the return value.
     * NOTE: this is optional because the ASL language does not actually
     * support this behavior.
     */
    (void) AcpiDsDoImplicitReturn (WalkState->ResultObj, WalkState, TRUE);

    /*
     * Now determine if the parent will use the result
     *
     * If there is no parent, or the parent is a ScopeOp, we are executing
     * at the method level. An executing method typically has no parent,
     * since each method is parsed separately. A method invoked externally
     * via ExecuteControlMethod has a ScopeOp as the parent.
     */
    if ((!Op->Common.Parent) ||
        (Op->Common.Parent->Common.AmlOpcode == AML_SCOPE_OP))
    {
        /* No parent, the return value cannot possibly be used */

        ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
            "At Method level, result of [%s] not used\n",
            AcpiPsGetOpcodeName (Op->Common.AmlOpcode)));
        return_UINT8 (FALSE);
    }

    /* Get info on the parent. The RootOp is AML_SCOPE */

    ParentInfo = AcpiPsGetOpcodeInfo (Op->Common.Parent->Common.AmlOpcode);
    if (ParentInfo->Class == AML_CLASS_UNKNOWN)
    {
        ACPI_ERROR ((AE_INFO,
            "Unknown parent opcode Op=%p", Op));
        return_UINT8 (FALSE);
    }

    /*
     * Decide what to do with the result based on the parent. If
     * the parent opcode will not use the result, delete the object.
     * Otherwise leave it as is, it will be deleted when it is used
     * as an operand later.
     */
    switch (ParentInfo->Class)
    {
    case AML_CLASS_CONTROL:

        switch (Op->Common.Parent->Common.AmlOpcode)
        {
        case AML_RETURN_OP:

            /* Never delete the return value associated with a return opcode */

            goto ResultUsed;

        case AML_IF_OP:
        case AML_WHILE_OP:
            /*
             * If we are executing the predicate AND this is the predicate op,
             * we will use the return value
             */
            if ((WalkState->ControlState->Common.State ==
                    ACPI_CONTROL_PREDICATE_EXECUTING) &&
                (WalkState->ControlState->Control.PredicateOp == Op))
            {
                goto ResultUsed;
            }
            break;

        default:

            /* Ignore other control opcodes */

            break;
        }

        /* The general control opcode returns no result */

        goto ResultNotUsed;

    case AML_CLASS_CREATE:
        /*
         * These opcodes allow TermArg(s) as operands and therefore
         * the operands can be method calls. The result is used.
         */
        goto ResultUsed;

    case AML_CLASS_NAMED_OBJECT:

        if ((Op->Common.Parent->Common.AmlOpcode == AML_REGION_OP)       ||
            (Op->Common.Parent->Common.AmlOpcode == AML_DATA_REGION_OP)  ||
            (Op->Common.Parent->Common.AmlOpcode == AML_PACKAGE_OP)      ||
            (Op->Common.Parent->Common.AmlOpcode == AML_BUFFER_OP)       ||
            (Op->Common.Parent->Common.AmlOpcode == AML_VARIABLE_PACKAGE_OP) ||
            (Op->Common.Parent->Common.AmlOpcode == AML_INT_EVAL_SUBTREE_OP) ||
            (Op->Common.Parent->Common.AmlOpcode == AML_BANK_FIELD_OP))
        {
            /*
             * These opcodes allow TermArg(s) as operands and therefore
             * the operands can be method calls. The result is used.
             */
            goto ResultUsed;
        }

        goto ResultNotUsed;

    default:
        /*
         * In all other cases. the parent will actually use the return
         * object, so keep it.
         */
        goto ResultUsed;
    }


ResultUsed:
    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
        "Result of [%s] used by Parent [%s] Op=%p\n",
        AcpiPsGetOpcodeName (Op->Common.AmlOpcode),
        AcpiPsGetOpcodeName (Op->Common.Parent->Common.AmlOpcode), Op));

    return_UINT8 (TRUE);


ResultNotUsed:
    ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
        "Result of [%s] not used by Parent [%s] Op=%p\n",
        AcpiPsGetOpcodeName (Op->Common.AmlOpcode),
        AcpiPsGetOpcodeName (Op->Common.Parent->Common.AmlOpcode), Op));

    return_UINT8 (FALSE);
}