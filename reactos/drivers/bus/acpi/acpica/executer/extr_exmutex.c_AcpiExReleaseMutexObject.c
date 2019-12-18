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
struct TYPE_6__ {scalar_t__ AcquisitionDepth; scalar_t__ ThreadId; int /*<<< orphan*/  OsMutex; int /*<<< orphan*/ * OwnerThread; } ;
struct TYPE_7__ {TYPE_1__ Mutex; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_2__ ACPI_OPERAND_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_NOT_ACQUIRED ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiEvReleaseGlobalLock () ; 
 int /*<<< orphan*/  AcpiExUnlinkMutex (TYPE_2__*) ; 
 TYPE_2__* AcpiGbl_GlobalLockMutex ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExReleaseMutexObject ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiExReleaseMutexObject (
    ACPI_OPERAND_OBJECT     *ObjDesc)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE (ExReleaseMutexObject);


    if (ObjDesc->Mutex.AcquisitionDepth == 0)
    {
        return_ACPI_STATUS (AE_NOT_ACQUIRED);
    }

    /* Match multiple Acquires with multiple Releases */

    ObjDesc->Mutex.AcquisitionDepth--;
    if (ObjDesc->Mutex.AcquisitionDepth != 0)
    {
        /* Just decrement the depth and return */

        return_ACPI_STATUS (AE_OK);
    }

    if (ObjDesc->Mutex.OwnerThread)
    {
        /* Unlink the mutex from the owner's list */

        AcpiExUnlinkMutex (ObjDesc);
        ObjDesc->Mutex.OwnerThread = NULL;
    }

    /* Release the mutex, special case for Global Lock */

    if (ObjDesc == AcpiGbl_GlobalLockMutex)
    {
        Status = AcpiEvReleaseGlobalLock ();
    }
    else
    {
        AcpiOsReleaseMutex (ObjDesc->Mutex.OsMutex);
    }

    /* Clear mutex info */

    ObjDesc->Mutex.ThreadId = 0;
    return_ACPI_STATUS (Status);
}