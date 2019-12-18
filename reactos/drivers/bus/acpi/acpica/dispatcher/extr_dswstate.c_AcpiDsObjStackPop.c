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
struct TYPE_3__ {size_t NumOperands; int /*<<< orphan*/ ** Operands; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_STACK_UNDERFLOW ; 
 int /*<<< orphan*/  DsObjStackPop ; 

ACPI_STATUS
AcpiDsObjStackPop (
    UINT32                  PopCount,
    ACPI_WALK_STATE         *WalkState)
{
    UINT32                  i;


    ACPI_FUNCTION_NAME (DsObjStackPop);


    for (i = 0; i < PopCount; i++)
    {
        /* Check for stack underflow */

        if (WalkState->NumOperands == 0)
        {
            ACPI_ERROR ((AE_INFO,
                "Object stack underflow! Count=%X State=%p #Ops=%u",
                PopCount, WalkState, WalkState->NumOperands));
            return (AE_STACK_UNDERFLOW);
        }

        /* Just set the stack entry to null */

        WalkState->NumOperands--;
        WalkState->Operands [WalkState->NumOperands] = NULL;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_EXEC, "Count=%X State=%p #Ops=%u\n",
        PopCount, WalkState, WalkState->NumOperands));

    return (AE_OK);
}