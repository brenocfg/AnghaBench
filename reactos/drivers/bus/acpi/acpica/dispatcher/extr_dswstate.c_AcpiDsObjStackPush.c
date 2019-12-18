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
struct TYPE_3__ {scalar_t__ NumOperands; size_t OperandIndex; void** Operands; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_OBJ_NUM_OPERANDS ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_STACK_OVERFLOW ; 
 int /*<<< orphan*/  AcpiUtGetObjectTypeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsObjStackPush ; 

ACPI_STATUS
AcpiDsObjStackPush (
    void                    *Object,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_FUNCTION_NAME (DsObjStackPush);


    /* Check for stack overflow */

    if (WalkState->NumOperands >= ACPI_OBJ_NUM_OPERANDS)
    {
        ACPI_ERROR ((AE_INFO,
            "Object stack overflow! Obj=%p State=%p #Ops=%u",
            Object, WalkState, WalkState->NumOperands));
        return (AE_STACK_OVERFLOW);
    }

    /* Put the object onto the stack */

    WalkState->Operands [WalkState->OperandIndex] = Object;
    WalkState->NumOperands++;

    /* For the usual order of filling the operand stack */

    WalkState->OperandIndex++;

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Obj=%p [%s] State=%p #Ops=%X\n",
        Object, AcpiUtGetObjectTypeName ((ACPI_OPERAND_OBJECT *) Object),
        WalkState, WalkState->NumOperands));

    return (AE_OK);
}