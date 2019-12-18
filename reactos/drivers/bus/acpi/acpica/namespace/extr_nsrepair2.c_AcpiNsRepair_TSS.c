#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  Node; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;
typedef  TYPE_1__ ACPI_EVALUATE_INFO ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_NS_NO_UPSEARCH ; 
 int /*<<< orphan*/  ACPI_SORT_DESCENDING ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiNsCheckSortedList (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  AcpiNsGetNode (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static ACPI_STATUS
AcpiNsRepair_TSS (
    ACPI_EVALUATE_INFO      *Info,
    ACPI_OPERAND_OBJECT     **ReturnObjectPtr)
{
    ACPI_OPERAND_OBJECT     *ReturnObject = *ReturnObjectPtr;
    ACPI_STATUS             Status;
    ACPI_NAMESPACE_NODE     *Node;


    /*
     * We can only sort the _TSS return package if there is no _PSS in the
     * same scope. This is because if _PSS is present, the ACPI specification
     * dictates that the _TSS Power Dissipation field is to be ignored, and
     * therefore some BIOSs leave garbage values in the _TSS Power field(s).
     * In this case, it is best to just return the _TSS package as-is.
     * (May, 2011)
     */
    Status = AcpiNsGetNode (Info->Node, "^_PSS",
        ACPI_NS_NO_UPSEARCH, &Node);
    if (ACPI_SUCCESS (Status))
    {
        return (AE_OK);
    }

    Status = AcpiNsCheckSortedList (Info, ReturnObject, 0, 5, 1,
        ACPI_SORT_DESCENDING, "PowerDissipation");

    return (Status);
}