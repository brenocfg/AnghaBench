#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_8__ {int Flags; size_t MaxTableCount; size_t CurrentTableCount; TYPE_1__* Tables; } ;
struct TYPE_7__ {scalar_t__ Address; } ;
typedef  TYPE_1__ ACPI_TABLE_DESC ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int ACPI_SIZE ;

/* Variables and functions */
 TYPE_1__* ACPI_ALLOCATE_ZEROED (int) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FREE (TYPE_1__*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int ACPI_ROOT_ALLOW_RESIZE ; 
 int ACPI_ROOT_ORIGIN_ALLOCATED ; 
 size_t ACPI_ROOT_TABLE_SIZE_INCREMENT ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_SUPPORT ; 
 TYPE_4__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  TbResizeRootTableList ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiTbResizeRootTableList (
    void)
{
    ACPI_TABLE_DESC         *Tables;
    UINT32                  TableCount;
    UINT32                  CurrentTableCount, MaxTableCount;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (TbResizeRootTableList);


    /* AllowResize flag is a parameter to AcpiInitializeTables */

    if (!(AcpiGbl_RootTableList.Flags & ACPI_ROOT_ALLOW_RESIZE))
    {
        ACPI_ERROR ((AE_INFO, "Resize of Root Table Array is not allowed"));
        return_ACPI_STATUS (AE_SUPPORT);
    }

    /* Increase the Table Array size */

    if (AcpiGbl_RootTableList.Flags & ACPI_ROOT_ORIGIN_ALLOCATED)
    {
        TableCount = AcpiGbl_RootTableList.MaxTableCount;
    }
    else
    {
        TableCount = AcpiGbl_RootTableList.CurrentTableCount;
    }

    MaxTableCount = TableCount + ACPI_ROOT_TABLE_SIZE_INCREMENT;
    Tables = ACPI_ALLOCATE_ZEROED (
        ((ACPI_SIZE) MaxTableCount) * sizeof (ACPI_TABLE_DESC));
    if (!Tables)
    {
        ACPI_ERROR ((AE_INFO, "Could not allocate new root table array"));
        return_ACPI_STATUS (AE_NO_MEMORY);
    }

    /* Copy and free the previous table array */

    CurrentTableCount = 0;
    if (AcpiGbl_RootTableList.Tables)
    {
        for (i = 0; i < TableCount; i++)
        {
            if (AcpiGbl_RootTableList.Tables[i].Address)
            {
                memcpy (Tables + CurrentTableCount,
                    AcpiGbl_RootTableList.Tables + i,
                    sizeof (ACPI_TABLE_DESC));
                CurrentTableCount++;
            }
        }

        if (AcpiGbl_RootTableList.Flags & ACPI_ROOT_ORIGIN_ALLOCATED)
        {
            ACPI_FREE (AcpiGbl_RootTableList.Tables);
        }
    }

    AcpiGbl_RootTableList.Tables = Tables;
    AcpiGbl_RootTableList.MaxTableCount = MaxTableCount;
    AcpiGbl_RootTableList.CurrentTableCount = CurrentTableCount;
    AcpiGbl_RootTableList.Flags |= ACPI_ROOT_ORIGIN_ALLOCATED;

    return_ACPI_STATUS (AE_OK);
}