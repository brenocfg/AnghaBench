#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  AmlOpcode; } ;
struct TYPE_17__ {TYPE_1__ Common; } ;
struct TYPE_16__ {scalar_t__ (* AscendingCallback ) (TYPE_2__*) ;int /*<<< orphan*/  ArgCount; int /*<<< orphan*/  ArgTypes; int /*<<< orphan*/  ParserState; int /*<<< orphan*/  Opcode; int /*<<< orphan*/  OpInfo; TYPE_3__* Op; } ;
typedef  TYPE_2__ ACPI_WALK_STATE ;
typedef  scalar_t__ ACPI_STATUS ;
typedef  TYPE_3__ ACPI_PARSE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ AE_CTRL_PENDING ; 
 scalar_t__ AE_CTRL_TERMINATE ; 
 scalar_t__ AE_OK ; 
 scalar_t__ AcpiPsCompleteOp (TYPE_2__*,TYPE_3__**,scalar_t__) ; 
 scalar_t__ AcpiPsCompleteThisOp (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiPsGetOpcodeInfo (int /*<<< orphan*/ ) ; 
 scalar_t__ AcpiPsNextParseState (TYPE_2__*,TYPE_3__*,scalar_t__) ; 
 int /*<<< orphan*/  AcpiPsPopScope (int /*<<< orphan*/ *,TYPE_3__**,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PsCompleteFinalOp ; 
 int /*<<< orphan*/  return_ACPI_STATUS (scalar_t__) ; 
 scalar_t__ stub1 (TYPE_2__*) ; 

ACPI_STATUS
AcpiPsCompleteFinalOp (
    ACPI_WALK_STATE         *WalkState,
    ACPI_PARSE_OBJECT       *Op,
    ACPI_STATUS             Status)
{
    ACPI_STATUS             Status2;


    ACPI_FUNCTION_TRACE_PTR (PsCompleteFinalOp, WalkState);


    /*
     * Complete the last Op (if not completed), and clear the scope stack.
     * It is easily possible to end an AML "package" with an unbounded number
     * of open scopes (such as when several ASL blocks are closed with
     * sequential closing braces). We want to terminate each one cleanly.
     */
    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE, "AML package complete at Op %p\n", Op));
    do
    {
        if (Op)
        {
            if (WalkState->AscendingCallback != NULL)
            {
                WalkState->Op = Op;
                WalkState->OpInfo = AcpiPsGetOpcodeInfo (Op->Common.AmlOpcode);
                WalkState->Opcode = Op->Common.AmlOpcode;

                Status = WalkState->AscendingCallback (WalkState);
                Status = AcpiPsNextParseState (WalkState, Op, Status);
                if (Status == AE_CTRL_PENDING)
                {
                    Status = AcpiPsCompleteOp (WalkState, &Op, AE_OK);
                    if (ACPI_FAILURE (Status))
                    {
                        return_ACPI_STATUS (Status);
                    }
                }

                if (Status == AE_CTRL_TERMINATE)
                {
                    Status = AE_OK;

                    /* Clean up */
                    do
                    {
                        if (Op)
                        {
                            Status2 = AcpiPsCompleteThisOp (WalkState, Op);
                            if (ACPI_FAILURE (Status2))
                            {
                                return_ACPI_STATUS (Status2);
                            }
                        }

                        AcpiPsPopScope (&(WalkState->ParserState), &Op,
                            &WalkState->ArgTypes, &WalkState->ArgCount);

                    } while (Op);

                    return_ACPI_STATUS (Status);
                }

                else if (ACPI_FAILURE (Status))
                {
                    /* First error is most important */

                    (void) AcpiPsCompleteThisOp (WalkState, Op);
                    return_ACPI_STATUS (Status);
                }
            }

            Status2 = AcpiPsCompleteThisOp (WalkState, Op);
            if (ACPI_FAILURE (Status2))
            {
                return_ACPI_STATUS (Status2);
            }
        }

        AcpiPsPopScope (&(WalkState->ParserState), &Op, &WalkState->ArgTypes,
            &WalkState->ArgCount);

    } while (Op);

    return_ACPI_STATUS (Status);
}