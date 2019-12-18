#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* WalkStateList; } ;
struct TYPE_6__ {struct TYPE_6__* Next; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;
typedef  TYPE_2__ ACPI_THREAD_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DsPopWalkState ; 
 int /*<<< orphan*/  return_PTR (TYPE_1__*) ; 

ACPI_WALK_STATE *
AcpiDsPopWalkState (
    ACPI_THREAD_STATE       *Thread)
{
    ACPI_WALK_STATE         *WalkState;


    ACPI_FUNCTION_TRACE (DsPopWalkState);


    WalkState = Thread->WalkStateList;

    if (WalkState)
    {
        /* Next walk state becomes the current walk state */

        Thread->WalkStateList = WalkState->Next;

        /*
         * Don't clear the NEXT field, this serves as an indicator
         * that there is a parent WALK STATE
         * Do Not: WalkState->Next = NULL;
         */
    }

    return_PTR (WalkState);
}