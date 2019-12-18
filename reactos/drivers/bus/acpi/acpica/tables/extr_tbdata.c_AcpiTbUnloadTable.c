#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  UINT32 ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TABLE_EVENT_UNLOAD ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiGetTableByIndex (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  AcpiTbDeleteNamespaceByOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTbIsTableLoaded (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTbNotifyTable (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbReleaseOwnerId (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiTbSetTableLoadedFlag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TbUnloadTable ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiTbUnloadTable (
    UINT32                  TableIndex)
{
    ACPI_STATUS             Status = AE_OK;
    ACPI_TABLE_HEADER       *Table;


    ACPI_FUNCTION_TRACE (TbUnloadTable);


    /* Ensure the table is still loaded */

    if (!AcpiTbIsTableLoaded (TableIndex))
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /* Invoke table handler */

    Status = AcpiGetTableByIndex (TableIndex, &Table);
    if (ACPI_SUCCESS (Status))
    {
        AcpiTbNotifyTable (ACPI_TABLE_EVENT_UNLOAD, Table);
    }

    /* Delete the portion of the namespace owned by this table */

    Status = AcpiTbDeleteNamespaceByOwner (TableIndex);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    (void) AcpiTbReleaseOwnerId (TableIndex);
    AcpiTbSetTableLoadedFlag (TableIndex, FALSE);
    return_ACPI_STATUS (Status);
}