#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* WalkStateList; } ;
struct TYPE_5__ {struct TYPE_5__* Next; } ;
typedef  TYPE_1__ ACPI_WALK_STATE ;
typedef  TYPE_2__ ACPI_THREAD_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DsPushWalkState ; 
 int /*<<< orphan*/  return_VOID ; 

void
AcpiDsPushWalkState (
    ACPI_WALK_STATE         *WalkState,
    ACPI_THREAD_STATE       *Thread)
{
    ACPI_FUNCTION_TRACE (DsPushWalkState);


    WalkState->Next = Thread->WalkStateList;
    Thread->WalkStateList = WalkState;

    return_VOID;
}