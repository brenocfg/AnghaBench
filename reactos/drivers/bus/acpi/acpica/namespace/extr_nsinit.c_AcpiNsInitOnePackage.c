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
typedef  int /*<<< orphan*/  UINT32 ;
struct TYPE_6__ {int Flags; } ;
struct TYPE_7__ {TYPE_1__ Package; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  scalar_t__ ACPI_HANDLE ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int AOPOBJ_DATA_VALID ; 
 int /*<<< orphan*/  AcpiDsGetPackageArguments (TYPE_2__*) ; 
 int /*<<< orphan*/  AcpiDsInitPackageElement ; 
 TYPE_2__* AcpiNsGetAttachedObject (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtWalkPackageTree (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

ACPI_STATUS
AcpiNsInitOnePackage (
    ACPI_HANDLE             ObjHandle,
    UINT32                  Level,
    void                    *Context,
    void                    **ReturnValue)
{
    ACPI_STATUS             Status;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_NAMESPACE_NODE     *Node = (ACPI_NAMESPACE_NODE *) ObjHandle;


    ObjDesc = AcpiNsGetAttachedObject (Node);
    if (!ObjDesc)
    {
        return (AE_OK);
    }

    /* Exit if package is already initialized */

    if (ObjDesc->Package.Flags & AOPOBJ_DATA_VALID)
    {
        return (AE_OK);
    }

    Status = AcpiDsGetPackageArguments (ObjDesc);
    if (ACPI_FAILURE (Status))
    {
        return (AE_OK);
    }

    Status = AcpiUtWalkPackageTree (ObjDesc, NULL, AcpiDsInitPackageElement,
        NULL);
    if (ACPI_FAILURE (Status))
    {
        return (AE_OK);
    }

    ObjDesc->Package.Flags |= AOPOBJ_DATA_VALID;
    return (AE_OK);
}