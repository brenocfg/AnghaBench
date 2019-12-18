#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  Elements; scalar_t__ Count; } ;
struct TYPE_9__ {int /*<<< orphan*/  Flags; int /*<<< orphan*/  Type; } ;
struct TYPE_11__ {TYPE_2__ Package; TYPE_1__ Common; } ;
typedef  int /*<<< orphan*/  ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_SIZE ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiUtCopyIelementToIelement ; 
 int /*<<< orphan*/  AcpiUtRemoveReference (TYPE_3__*) ; 
 int /*<<< orphan*/  AcpiUtWalkPackageTree (TYPE_3__*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UtCopyIpackageToIpackage ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtCopyIpackageToIpackage (
    ACPI_OPERAND_OBJECT     *SourceObj,
    ACPI_OPERAND_OBJECT     *DestObj,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (UtCopyIpackageToIpackage);


    DestObj->Common.Type = SourceObj->Common.Type;
    DestObj->Common.Flags = SourceObj->Common.Flags;
    DestObj->Package.Count = SourceObj->Package.Count;

    /*
     * Create the object array and walk the source package tree
     */
    DestObj->Package.Elements = ACPI_ALLOCATE_ZEROED (
        ((ACPI_SIZE) SourceObj->Package.Count + 1) *
        sizeof (void *));
    if (!DestObj->Package.Elements)
    {
        ACPI_ERROR ((AE_INFO, "Package allocation failure"));
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /*
     * Copy the package element-by-element by walking the package "tree".
     * This handles nested packages of arbitrary depth.
     */
    Status = AcpiUtWalkPackageTree (SourceObj, DestObj,
        AcpiUtCopyIelementToIelement, WalkState);
    if (ACPI_FAILURE (Status))
    {
        /* On failure, delete the destination package object */

        AcpiUtRemoveReference (DestObj);
    }

    return_ACPI_STATUS (Status);
}