#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT32 ;
struct TYPE_7__ {int /*<<< orphan*/  Ascii; } ;
struct TYPE_9__ {TYPE_1__ Name; } ;
struct TYPE_8__ {scalar_t__ UnexpectedBtypes; scalar_t__ PackageIndex; int /*<<< orphan*/  Name; scalar_t__ ObjectConverter; } ;
typedef  TYPE_2__ ACPI_SIMPLE_REPAIR_INFO ;
typedef  TYPE_3__ ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 scalar_t__ ACPI_ALL_PACKAGE_ELEMENTS ; 
 scalar_t__ ACPI_COMPARE_NAMESEG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* AcpiObjectRepairInfo ; 

__attribute__((used)) static const ACPI_SIMPLE_REPAIR_INFO *
AcpiNsMatchSimpleRepair (
    ACPI_NAMESPACE_NODE     *Node,
    UINT32                  ReturnBtype,
    UINT32                  PackageIndex)
{
    const ACPI_SIMPLE_REPAIR_INFO   *ThisName;


    /* Search info table for a repairable predefined method/object name */

    ThisName = AcpiObjectRepairInfo;
    while (ThisName->ObjectConverter)
    {
        if (ACPI_COMPARE_NAMESEG (Node->Name.Ascii, ThisName->Name))
        {
            /* Check if we can actually repair this name/type combination */

            if ((ReturnBtype & ThisName->UnexpectedBtypes) &&
                (ThisName->PackageIndex == ACPI_ALL_PACKAGE_ELEMENTS ||
                 PackageIndex == ThisName->PackageIndex))
            {
                return (ThisName);
            }

            return (NULL);
        }

        ThisName++;
    }

    return (NULL); /* Name was not found in the repair table */
}