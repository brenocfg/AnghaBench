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
struct TYPE_3__ {int /*<<< orphan*/ * ImplicitReturnObj; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_DISPATCH ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiGbl_EnableInterpreterSlack ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsClearImplicitReturn ; 

void
AcpiDsClearImplicitReturn (
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_FUNCTION_NAME (DsClearImplicitReturn);


    /*
     * Slack must be enabled for this feature
     */
    if (!AcpiGbl_EnableInterpreterSlack)
    {
        return;
    }

    if (WalkState->ImplicitReturnObj)
    {
        /*
         * Delete any "stale" implicit return. However, in
         * complex statements, the implicit return value can be
         * bubbled up several levels.
         */
        ACPI_DEBUG_PRINT ((ACPI_DB_DISPATCH,
            "Removing reference on stale implicit return obj %p\n",
            WalkState->ImplicitReturnObj));

        AcpiUtRemoveReference (WalkState->ImplicitReturnObj);
        WalkState->ImplicitReturnObj = NULL;
    }
}