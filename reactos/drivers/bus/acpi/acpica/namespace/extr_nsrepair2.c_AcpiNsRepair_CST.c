#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int UINT32 ;
struct TYPE_13__ {int /*<<< orphan*/  NodeFlags; int /*<<< orphan*/  FullPathname; } ;
struct TYPE_11__ {int Value; } ;
struct TYPE_10__ {int Count; TYPE_3__** Elements; } ;
struct TYPE_12__ {TYPE_2__ Integer; TYPE_1__ Package; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_3__ ACPI_OPERAND_OBJECT ;
typedef  TYPE_4__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SORT_ASCENDING ; 
 int /*<<< orphan*/  ACPI_WARN_PREDEFINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsCheckSortedList (TYPE_4__*,TYPE_3__*,int,int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AcpiNsRemoveElement (TYPE_3__*,int) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  NsRepair_CST ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsRepair_CST (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT     *ReturnObject = *ReturnObjectPtr;
    ACPI_OPERAND_OBJECT     **OuterElements;
    UINT32                  OuterElementCount;
    ACPI_OPERAND_OBJECT     *ObjDesc;
    ACPI_STATUS             Status;
    BOOLEAN                 Removing;
    UINT32                  i;


    ACPI_FUNCTION_NAME (NsRepair_CST);


    /*
     * Check if the C-state type values are proportional.
     */
    OuterElementCount = ReturnObject->Package.Count - 1;
    i = 0;
    while (i < OuterElementCount)
    {
        OuterElements = &ReturnObject->Package.Elements[i + 1];
        Removing = FALSE;

        if ((*OuterElements)->Package.Count == 0)
        {
            ACPI_WARN_PREDEFINED ((AE_INFO,
                Info->FullPathname, Info->NodeFlags,
                "SubPackage[%u] - removing entry due to zero count", i));
            Removing = TRUE;
            goto RemoveElement;
        }

        ObjDesc = (*OuterElements)->Package.Elements[1]; /* Index1 = Type */
        if ((UINT32) ObjDesc->Integer.Value == 0)
        {
            ACPI_WARN_PREDEFINED ((AE_INFO,
                Info->FullPathname, Info->NodeFlags,
                "SubPackage[%u] - removing entry due to invalid Type(0)", i));
            Removing = TRUE;
        }

RemoveElement:
        if (Removing)
        {
            AcpiNsRemoveElement (ReturnObject, i + 1);
            OuterElementCount--;
        }
        else
        {
            i++;
        }
    }

    /* Update top-level package count, Type "Integer" checked elsewhere */

    ObjDesc = ReturnObject->Package.Elements[0];
    ObjDesc->Integer.Value = OuterElementCount;

    /*
     * Entries (subpackages) in the _CST Package must be sorted by the
     * C-state type, in ascending order.
     */
    Status = AcpiNsCheckSortedList (Info, ReturnObject, 1, 4, 1,
        ACPI_SORT_ASCENDING, "C-State Type");
    if (ACPI_FAILURE (Status))
    {
        return (Status);
    }

    return (AE_OK);
}