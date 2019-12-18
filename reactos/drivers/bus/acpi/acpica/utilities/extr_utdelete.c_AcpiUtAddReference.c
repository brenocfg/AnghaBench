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
struct TYPE_6__ {int /*<<< orphan*/  ReferenceCount; } ;
struct TYPE_7__ {TYPE_1__ Common; } ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ALLOCATIONS ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtUpdateObjectReference (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtValidInternalObject (TYPE_2__*) ; 
 int /*<<< orphan*/  REF_INCREMENT ; 
 int /*<<< orphan*/  UtAddReference ; 

void
AcpiUtAddReference (
    ACPI_OPERAND_OBJECT     *Object)
{

    ACPI_FUNCTION_NAME (UtAddReference);


    /* Ensure that we have a valid object */

    if (!AcpiUtValidInternalObject (Object))
    {
        return;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_ALLOCATIONS,
        "Obj %p Current Refs=%X [To Be Incremented]\n",
        Object, Object->Common.ReferenceCount));

    /* Increment the reference count */

    (void) AcpiUtUpdateObjectReference (Object, REF_INCREMENT);
    return;
}