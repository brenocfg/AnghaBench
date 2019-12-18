#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_4__ {size_t CurrentTableCount; TYPE_1__* Tables; } ;
struct TYPE_3__ {int /*<<< orphan*/  OwnerId; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  int /*<<< orphan*/  ACPI_OWNER_ID ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MTX_TABLES ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int /*<<< orphan*/  AcpiGbl_NamespaceRwLock ; 
 TYPE_2__ AcpiGbl_RootTableList ; 
 int /*<<< orphan*/  AcpiNsDeleteNamespaceByOwner (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtAcquireMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtAcquireWriteLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtReleaseWriteLock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TbDeleteNamespaceByOwner ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiTbDeleteNamespaceByOwner (
    UINT32                  TableIndex)
{
    ACPI_OWNER_ID           OwnerId;
    ACPI_STATUS             Status;


    ACPI_FUNCTION_TRACE (TbDeleteNamespaceByOwner);


    Status = AcpiUtAcquireMutex (ACPI_MTX_TABLES);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (TableIndex >= AcpiGbl_RootTableList.CurrentTableCount)
    {
        /* The table index does not exist */

        (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /* Get the owner ID for this table, used to delete namespace nodes */

    OwnerId = AcpiGbl_RootTableList.Tables[TableIndex].OwnerId;
    (void) AcpiUtReleaseMutex (ACPI_MTX_TABLES);

    /*
     * Need to acquire the namespace writer lock to prevent interference
     * with any concurrent namespace walks. The interpreter must be
     * released during the deletion since the acquisition of the deletion
     * lock may block, and also since the execution of a namespace walk
     * must be allowed to use the interpreter.
     */
    Status = AcpiUtAcquireWriteLock (&AcpiGbl_NamespaceRwLock);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    AcpiNsDeleteNamespaceByOwner (OwnerId);
    AcpiUtReleaseWriteLock (&AcpiGbl_NamespaceRwLock);
    return_ACPI_STATUS (Status);
}