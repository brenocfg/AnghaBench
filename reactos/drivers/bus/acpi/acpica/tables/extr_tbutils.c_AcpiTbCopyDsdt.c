#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_13__ {TYPE_2__* Tables; } ;
struct TYPE_12__ {int /*<<< orphan*/  Length; int /*<<< orphan*/  Pointer; } ;
struct TYPE_11__ {int /*<<< orphan*/  Length; } ;
typedef  TYPE_1__ ACPI_TABLE_HEADER ;
typedef  TYPE_2__ ACPI_TABLE_DESC ;

/* Variables and functions */
 TYPE_1__* ACPI_ALLOCATE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_INFO (char*) ; 
 int /*<<< orphan*/  ACPI_PTR_TO_PHYSADDR (TYPE_1__*) ; 
 int /*<<< orphan*/  ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL ; 
 int /*<<< orphan*/  AE_INFO ; 
 size_t AcpiGbl_DsdtIndex ; 
 TYPE_8__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  AcpiTbInitTableDescriptor (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  AcpiTbUninstallTable (TYPE_2__*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ACPI_TABLE_HEADER *
AcpiTbCopyDsdt (
    UINT32                  TableIndex)
{
    ACPI_TABLE_HEADER       *NewTable;
    ACPI_TABLE_DESC         *TableDesc;


    TableDesc = &AcpiGbl_RootTableList.Tables[TableIndex];

    NewTable = ACPI_ALLOCATE (TableDesc->Length);
    if (!NewTable)
    {
        ACPI_ERROR ((AE_INFO, "Could not copy DSDT of length 0x%X",
            TableDesc->Length));
        return (NULL);
    }

    memcpy (NewTable, TableDesc->Pointer, TableDesc->Length);
    AcpiTbUninstallTable (TableDesc);

    AcpiTbInitTableDescriptor (
        &AcpiGbl_RootTableList.Tables[AcpiGbl_DsdtIndex],
        ACPI_PTR_TO_PHYSADDR (NewTable),
        ACPI_TABLE_ORIGIN_INTERNAL_VIRTUAL, NewTable);

    ACPI_INFO ((
        "Forced DSDT copy: length 0x%05X copied locally, original unmapped",
        NewTable->Length));

    return (NewTable);
}