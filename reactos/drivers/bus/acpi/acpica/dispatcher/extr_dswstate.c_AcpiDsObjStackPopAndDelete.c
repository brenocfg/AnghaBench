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
typedef  scalar_t__ UINT32 ;
struct TYPE_3__ {scalar_t__ NumOperands; int /*<<< orphan*/ ** Operands; } ;
typedef  size_t INT32 ;
typedef  TYPE_1__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsObjStackPopAndDelete ; 

void
AcpiDsObjStackPopAndDelete (
    UINT32                  PopCount,
    ACPI_WALK_STATE         *WalkState)
{
    INT32                   i;
    ACPI_OPERAND_OBJECT     *ObjDesc;


    ACPI_FUNCTION_NAME (DsObjStackPopAndDelete);


    if (PopCount == 0)
    {
        return;
    }

    for (i = (INT32) PopCount - 1; i >= 0; i--)
    {
        if (WalkState->NumOperands == 0)
        {
            return;
        }

        /* Pop the stack and delete an object if present in this stack entry */

        WalkState->NumOperands--;
        ObjDesc = WalkState->Operands [i];
        if (ObjDesc)
        {
            AcpiUtRemoveReference (WalkState->Operands [i]);
            WalkState->Operands [i] = NULL;
        }
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Count=%X State=%p #Ops=%X\n",
        PopCount, WalkState, WalkState->NumOperands));
}