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
struct TYPE_3__ {int /*<<< orphan*/ * WalkStateList; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  TYPE_1__ ACPI_THREAD_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_PARSE ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DsGetCurrentWalkState ; 

ACPI_WALK_STATE *
AcpiDsGetCurrentWalkState (
    ACPI_THREAD_STATE       *Thread)
{
    ACPI_FUNCTION_NAME (DsGetCurrentWalkState);


    if (!Thread)
    {
        return (NULL);
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_PARSE, "Current WalkState %p\n",
        Thread->WalkStateList));

    return (Thread->WalkStateList);
}