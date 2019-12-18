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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_8__ {int /*<<< orphan*/ * Handler; } ;
struct TYPE_7__ {scalar_t__ UseCount; int /*<<< orphan*/  ThreadId; int /*<<< orphan*/ * Mutex; } ;
struct TYPE_5__ {int /*<<< orphan*/  Integer; } ;
struct TYPE_6__ {int /*<<< orphan*/ * Object; int /*<<< orphan*/ * Peer; int /*<<< orphan*/ * Child; int /*<<< orphan*/ * Parent; int /*<<< orphan*/  Type; int /*<<< orphan*/  DescriptorType; TYPE_1__ Name; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;

/* Variables and functions */
 size_t ACPI_ADDRESS_RANGE_MAX ; 
 int /*<<< orphan*/  ACPI_CAST_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_DESC_TYPE_NAMED ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MUTEX_NOT_ACQUIRED ; 
 size_t ACPI_NUM_FIXED_EVENTS ; 
 size_t ACPI_NUM_MUTEX ; 
 size_t ACPI_NUM_OWNERID_MASKS ; 
 int /*<<< orphan*/  ACPI_ROOT_NAME ; 
 int /*<<< orphan*/  ACPI_SIZE ; 
 int /*<<< orphan*/  ACPI_SIZE_MAX ; 
 int /*<<< orphan*/  ACPI_TYPE_DEVICE ; 
 int /*<<< orphan*/  AE_OK ; 
 scalar_t__ AcpiCurrentGpeCount ; 
 scalar_t__* AcpiFixedEventCount ; 
 void* AcpiGbl_AcpiHardwarePresent ; 
 int /*<<< orphan*/ ** AcpiGbl_AddressRangeList ; 
 void* AcpiGbl_AllGpesInitialized ; 
 void* AcpiGbl_CmSingleStep ; 
 int /*<<< orphan*/ * AcpiGbl_DSDT ; 
 int /*<<< orphan*/  AcpiGbl_DebuggerConfiguration ; 
 void* AcpiGbl_DisableMemTracking ; 
 void* AcpiGbl_DisplayFinalMemStats ; 
 void* AcpiGbl_EventsInitialized ; 
 int /*<<< orphan*/ * AcpiGbl_ExceptionHandler ; 
 int /*<<< orphan*/ * AcpiGbl_ExternalList ; 
 int /*<<< orphan*/ * AcpiGbl_GlobalEventHandler ; 
 void* AcpiGbl_GlobalLockAcquired ; 
 scalar_t__ AcpiGbl_GlobalLockHandle ; 
 int /*<<< orphan*/ * AcpiGbl_GlobalLockMutex ; 
 void* AcpiGbl_GlobalLockPresent ; 
 int /*<<< orphan*/ * AcpiGbl_GlobalLockSemaphore ; 
 TYPE_4__* AcpiGbl_GlobalNotify ; 
 int /*<<< orphan*/ ** AcpiGbl_GpeFadtBlocks ; 
 int /*<<< orphan*/ * AcpiGbl_GpeXruptListHead ; 
 int /*<<< orphan*/ * AcpiGbl_InitHandler ; 
 int /*<<< orphan*/ * AcpiGbl_InterfaceHandler ; 
 scalar_t__ AcpiGbl_LastOwnerIdIndex ; 
 int /*<<< orphan*/  AcpiGbl_LowestStackPointer ; 
 TYPE_3__* AcpiGbl_MutexInfo ; 
 scalar_t__ AcpiGbl_NextOwnerIdOffset ; 
 scalar_t__ AcpiGbl_NsLookupCount ; 
 scalar_t__ AcpiGbl_NumExternalMethods ; 
 int /*<<< orphan*/ * AcpiGbl_OsiMutex ; 
 int* AcpiGbl_OwnerIdMask ; 
 scalar_t__ AcpiGbl_PsFindCount ; 
 scalar_t__ AcpiGbl_ResolvedExternalMethods ; 
 int /*<<< orphan*/ * AcpiGbl_RootNode ; 
 TYPE_2__ AcpiGbl_RootNodeStruct ; 
 int /*<<< orphan*/ * AcpiGbl_SciHandlerList ; 
 void* AcpiGbl_Shutdown ; 
 void* AcpiGbl_SystemAwakeAndRunning ; 
 int /*<<< orphan*/ * AcpiGbl_TableHandler ; 
 scalar_t__ AcpiGpeCount ; 
 scalar_t__ AcpiMethodCount ; 
 scalar_t__ AcpiSciCount ; 
 int /*<<< orphan*/  AcpiUtCreateCaches () ; 
 int /*<<< orphan*/  DEBUGGER_THREADING ; 
 void* FALSE ; 
 void* TRUE ; 
 int /*<<< orphan*/  UtInitGlobals ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiUtInitGlobals (
    void)
{
    ACPI_STATUS             Status;
    UINT32                  i;


    ACPI_FUNCTION_TRACE (UtInitGlobals);


    /* Create all memory caches */

    Status = AcpiUtCreateCaches ();
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Address Range lists */

    for (i = 0; i < ACPI_ADDRESS_RANGE_MAX; i++)
    {
        AcpiGbl_AddressRangeList[i] = NULL;
    }

    /* Mutex locked flags */

    for (i = 0; i < ACPI_NUM_MUTEX; i++)
    {
        AcpiGbl_MutexInfo[i].Mutex          = NULL;
        AcpiGbl_MutexInfo[i].ThreadId       = ACPI_MUTEX_NOT_ACQUIRED;
        AcpiGbl_MutexInfo[i].UseCount       = 0;
    }

    for (i = 0; i < ACPI_NUM_OWNERID_MASKS; i++)
    {
        AcpiGbl_OwnerIdMask[i]              = 0;
    }

    /* Last OwnerID is never valid */

    AcpiGbl_OwnerIdMask[ACPI_NUM_OWNERID_MASKS - 1] = 0x80000000;

    /* Event counters */

    AcpiMethodCount                     = 0;
    AcpiSciCount                        = 0;
    AcpiGpeCount                        = 0;

    for (i = 0; i < ACPI_NUM_FIXED_EVENTS; i++)
    {
        AcpiFixedEventCount[i]              = 0;
    }

#if (!ACPI_REDUCED_HARDWARE)

    /* GPE/SCI support */

    AcpiGbl_AllGpesInitialized          = FALSE;
    AcpiGbl_GpeXruptListHead            = NULL;
    AcpiGbl_GpeFadtBlocks[0]            = NULL;
    AcpiGbl_GpeFadtBlocks[1]            = NULL;
    AcpiCurrentGpeCount                 = 0;

    AcpiGbl_GlobalEventHandler          = NULL;
    AcpiGbl_SciHandlerList              = NULL;

#endif /* !ACPI_REDUCED_HARDWARE */

    /* Global handlers */

    AcpiGbl_GlobalNotify[0].Handler     = NULL;
    AcpiGbl_GlobalNotify[1].Handler     = NULL;
    AcpiGbl_ExceptionHandler            = NULL;
    AcpiGbl_InitHandler                 = NULL;
    AcpiGbl_TableHandler                = NULL;
    AcpiGbl_InterfaceHandler            = NULL;

    /* Global Lock support */

    AcpiGbl_GlobalLockSemaphore         = NULL;
    AcpiGbl_GlobalLockMutex             = NULL;
    AcpiGbl_GlobalLockAcquired          = FALSE;
    AcpiGbl_GlobalLockHandle            = 0;
    AcpiGbl_GlobalLockPresent           = FALSE;

    /* Miscellaneous variables */

    AcpiGbl_DSDT                        = NULL;
    AcpiGbl_CmSingleStep                = FALSE;
    AcpiGbl_Shutdown                    = FALSE;
    AcpiGbl_NsLookupCount               = 0;
    AcpiGbl_PsFindCount                 = 0;
    AcpiGbl_AcpiHardwarePresent         = TRUE;
    AcpiGbl_LastOwnerIdIndex            = 0;
    AcpiGbl_NextOwnerIdOffset           = 0;
    AcpiGbl_DebuggerConfiguration       = DEBUGGER_THREADING;
    AcpiGbl_OsiMutex                    = NULL;

    /* Hardware oriented */

    AcpiGbl_EventsInitialized           = FALSE;
    AcpiGbl_SystemAwakeAndRunning       = TRUE;

    /* Namespace */

    AcpiGbl_RootNode                    = NULL;
    AcpiGbl_RootNodeStruct.Name.Integer = ACPI_ROOT_NAME;
    AcpiGbl_RootNodeStruct.DescriptorType = ACPI_DESC_TYPE_NAMED;
    AcpiGbl_RootNodeStruct.Type         = ACPI_TYPE_DEVICE;
    AcpiGbl_RootNodeStruct.Parent       = NULL;
    AcpiGbl_RootNodeStruct.Child        = NULL;
    AcpiGbl_RootNodeStruct.Peer         = NULL;
    AcpiGbl_RootNodeStruct.Object       = NULL;


#ifdef ACPI_DISASSEMBLER
    AcpiGbl_ExternalList                = NULL;
    AcpiGbl_NumExternalMethods          = 0;
    AcpiGbl_ResolvedExternalMethods     = 0;
#endif

#ifdef ACPI_DEBUG_OUTPUT
    AcpiGbl_LowestStackPointer          = ACPI_CAST_PTR (ACPI_SIZE, ACPI_SIZE_MAX);
#endif

#ifdef ACPI_DBG_TRACK_ALLOCATIONS
    AcpiGbl_DisplayFinalMemStats        = FALSE;
    AcpiGbl_DisableMemTracking          = FALSE;
#endif

    return_ACPI_STATUS (AE_OK);
}