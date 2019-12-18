#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ ThreadCount; int InfoFlags; scalar_t__ SyncLevel; TYPE_3__* Mutex; int /*<<< orphan*/  OwnerId; } ;
struct TYPE_17__ {TYPE_4__ Method; } ;
struct TYPE_16__ {TYPE_1__* Thread; } ;
struct TYPE_13__ {scalar_t__ SyncLevel; scalar_t__ ThreadId; scalar_t__ OriginalSyncLevel; int /*<<< orphan*/  OsMutex; int /*<<< orphan*/  AcquisitionDepth; } ;
struct TYPE_14__ {TYPE_2__ Mutex; } ;
struct TYPE_12__ {scalar_t__ CurrentSyncLevel; scalar_t__ ThreadId; } ;
typedef  TYPE_5__ ACPI_WALK_STATE ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  TYPE_6__ ACPI_OPERAND_OBJECT ;
typedef  int /*<<< orphan*/  ACPI_NAMESPACE_NODE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ACPI_METHOD_IGNORE_SYNC_LEVEL ; 
 int ACPI_METHOD_SERIALIZED ; 
 scalar_t__ ACPI_UINT8_MAX ; 
 int /*<<< orphan*/  ACPI_WAIT_FOREVER ; 
 int /*<<< orphan*/  AE_AML_METHOD_LIMIT ; 
 int /*<<< orphan*/  AE_AML_MUTEX_ORDER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NULL_ENTRY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AcpiDsCreateMethodMutex (TYPE_6__*) ; 
 int /*<<< orphan*/  AcpiExStartTraceMethod (int /*<<< orphan*/ *,TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  AcpiExSystemWaitMutex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiMethodCount ; 
 scalar_t__ AcpiOsGetThreadId () ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtAllocateOwnerId (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AcpiUtGetNodeName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DsBeginMethodExecution ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiDsBeginMethodExecution (
    ACPI_NAMESPACE_NODE     *MethodNode,
    ACPI_OPERAND_OBJECT     *ObjDesc,
    ACPI_WALK_STATE         *WalkState)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE_PTR (DsBeginMethodExecution, MethodNode);


    if (!MethodNode)
    {
        return_ACPI_STATUS (AE_NULL_ENTRY);
    }

    AcpiExStartTraceMethod (MethodNode, ObjDesc, WalkState);

    /* Prevent wraparound of thread count */

    if (ObjDesc->Method.ThreadCount == ACPI_UINT8_MAX)
    {
        ACPI_ERROR ((AE_INFO,
            "Method reached maximum reentrancy limit (255)"));
        return_ACPI_STATUS (AE_AML_METHOD_LIMIT);
    }

    /*
     * If this method is serialized, we need to acquire the method mutex.
     */
    if (ObjDesc->Method.InfoFlags & ACPI_METHOD_SERIALIZED)
    {
        /*
         * Create a mutex for the method if it is defined to be Serialized
         * and a mutex has not already been created. We defer the mutex creation
         * until a method is actually executed, to minimize the object count
         */
        if (!ObjDesc->Method.Mutex)
        {
            Status = AcpiDsCreateMethodMutex (ObjDesc);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }
        }

        /*
         * The CurrentSyncLevel (per-thread) must be less than or equal to
         * the sync level of the method. This mechanism provides some
         * deadlock prevention.
         *
         * If the method was auto-serialized, we just ignore the sync level
         * mechanism, because auto-serialization of methods can interfere
         * with ASL code that actually uses sync levels.
         *
         * Top-level method invocation has no walk state at this point
         */
        if (WalkState &&
            (!(ObjDesc->Method.InfoFlags & ACPI_METHOD_IGNORE_SYNC_LEVEL)) &&
            (WalkState->Thread->CurrentSyncLevel >
                ObjDesc->Method.Mutex->Mutex.SyncLevel))
        {
            ACPI_ERROR ((AE_INFO,
                "Cannot acquire Mutex for method [%4.4s]"
                ", current SyncLevel is too large (%u)",
                AcpiUtGetNodeName (MethodNode),
                WalkState->Thread->CurrentSyncLevel));

            return_ACPI_STATUS (AE_AML_MUTEX_ORDER);
        }

        /*
         * Obtain the method mutex if necessary. Do not acquire mutex for a
         * recursive call.
         */
        if (!WalkState ||
            !ObjDesc->Method.Mutex->Mutex.ThreadId ||
            (WalkState->Thread->ThreadId !=
                ObjDesc->Method.Mutex->Mutex.ThreadId))
        {
            /*
             * Acquire the method mutex. This releases the interpreter if we
             * block (and reacquires it before it returns)
             */
            Status = AcpiExSystemWaitMutex (
                ObjDesc->Method.Mutex->Mutex.OsMutex, ACPI_WAIT_FOREVER);
            if (ACPI_FAILURE (Status))
            {
                return_ACPI_STATUS (Status);
            }

            /* Update the mutex and walk info and save the original SyncLevel */

            if (WalkState)
            {
                ObjDesc->Method.Mutex->Mutex.OriginalSyncLevel =
                    WalkState->Thread->CurrentSyncLevel;

                ObjDesc->Method.Mutex->Mutex.ThreadId =
                    WalkState->Thread->ThreadId;

                /*
                 * Update the current SyncLevel only if this is not an auto-
                 * serialized method. In the auto case, we have to ignore
                 * the sync level for the method mutex (created for the
                 * auto-serialization) because we have no idea of what the
                 * sync level should be. Therefore, just ignore it.
                 */
                if (!(ObjDesc->Method.InfoFlags &
                    ACPI_METHOD_IGNORE_SYNC_LEVEL))
                {
                    WalkState->Thread->CurrentSyncLevel =
                        ObjDesc->Method.SyncLevel;
                }
            }
            else
            {
                ObjDesc->Method.Mutex->Mutex.OriginalSyncLevel =
                    ObjDesc->Method.Mutex->Mutex.SyncLevel;

                ObjDesc->Method.Mutex->Mutex.ThreadId =
                    AcpiOsGetThreadId ();
            }
        }

        /* Always increase acquisition depth */

        ObjDesc->Method.Mutex->Mutex.AcquisitionDepth++;
    }

    /*
     * Allocate an Owner ID for this method, only if this is the first thread
     * to begin concurrent execution. We only need one OwnerId, even if the
     * method is invoked recursively.
     */
    if (!ObjDesc->Method.OwnerId)
    {
        Status = AcpiUtAllocateOwnerId (&ObjDesc->Method.OwnerId);
        if (ACPI_FAILURE (Status))
        {
            goto Cleanup;
        }
    }

    /*
     * Increment the method parse tree thread count since it has been
     * reentered one more time (even if it is the same thread)
     */
    ObjDesc->Method.ThreadCount++;
    AcpiMethodCount++;
    return_ACPI_STATUS (Status);


Cleanup:
    /* On error, must release the method mutex (if present) */

    if (ObjDesc->Method.Mutex)
    {
        AcpiOsReleaseMutex (ObjDesc->Method.Mutex->Mutex.OsMutex);
    }
    return_ACPI_STATUS (Status);
}