#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ Type; } ;
struct TYPE_12__ {TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_TYPE_PACKAGE ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiUtCopyIpackageToIpackage (TYPE_2__*,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtCopySimpleObject (TYPE_2__*,TYPE_2__*) ; 
 TYPE_2__* AcpiUtCreateInternalObject (scalar_t__) ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_2__*) ; 
 int /*<<< orphan*/  UtCopyIobjectToIobject ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtCopyIobjectToIobject (
    ACPI_OPERAND_OBJECT     *SourceDesc,
    ACPI_OPERAND_OBJECT     **DestDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (UtCopyIobjectToIobject);


    /* Create the top level object */

    *DestDesc = AcpiUtCreateInternalObject (SourceDesc->Common.Type);
    if (!*DestDesc)
    {
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Copy the object and possible subobjects */

    if (SourceDesc->Common.Type == ACPI_TYPE_PACKAGE)
    {
        Status = AcpiUtCopyIpackageToIpackage (
            SourceDesc, *DestDesc, WalkState);
    }
    else
    {
        Status = AcpiUtCopySimpleObject (SourceDesc, *DestDesc);
    }

    /* Delete the allocated object if copy failed */

    if (ACPI_FAILURE (Status))
    {
        AcpiUtRemoveReference (*DestDesc);
    }

    return_ACPI_STATUS (Status);
}