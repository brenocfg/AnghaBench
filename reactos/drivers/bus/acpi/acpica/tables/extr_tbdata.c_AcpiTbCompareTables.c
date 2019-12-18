#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT8 ;
typedef  size_t UINT32 ;
struct TYPE_5__ {int /*<<< orphan*/ * Tables; } ;
struct TYPE_4__ {size_t Length; int /*<<< orphan*/  Pointer; } ;
typedef  scalar_t__ BOOLEAN ;
typedef  int /*<<< orphan*/  ACPI_TABLE_HEADER ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_3__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  AcpiTbAcquireTable (int /*<<< orphan*/ *,int /*<<< orphan*/ **,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiTbReleaseTable (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static BOOLEAN
AcpiTbCompareTables (
    ACPI_TABLE_DESC         *TableDesc,
    UINT32                  TableIndex)
{
    ACPI_STATUS             Status = AE_OK;
    BOOLEAN                 IsIdentical;
    ACPI_TABLE_HEADER       *Table;
    UINT32                  TableLength;
    UINT8                   TableFlags;


    Status = AcpiTbAcquireTable (&AcpiGbl_RootTableList.Tables[TableIndex],
        &Table, &TableLength, &TableFlags);
    if (ACPI_FAILURE (Status))
    {
        return (FALSE);
    }

    /*
     * Check for a table match on the entire table length,
     * not just the header.
     */
    IsIdentical = (BOOLEAN)((TableDesc->Length != TableLength ||
        memcmp (TableDesc->Pointer, Table, TableLength)) ?
        FALSE : TRUE);

    /* Release the acquired table */

    AcpiTbReleaseTable (Table, TableLength, TableFlags);
    return (IsIdentical);
}