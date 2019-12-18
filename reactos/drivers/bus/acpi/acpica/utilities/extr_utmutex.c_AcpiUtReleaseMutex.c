#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT32 ;
struct TYPE_2__ {scalar_t__ ThreadId; int /*<<< orphan*/  Mutex; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  size_t ACPI_MUTEX_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_MUTEX ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_NAME (int /*<<< orphan*/ ) ; 
 size_t ACPI_MAX_MUTEX ; 
 scalar_t__ ACPI_MUTEX_NOT_ACQUIRED ; 
 size_t ACPI_NUM_MUTEX ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_ACQUIRED ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_RELEASE_DEADLOCK ; 
 TYPE_1__* AcpiGbl_MutexInfo ; 
 scalar_t__ AcpiOsGetThreadId () ; 
 int /*<<< orphan*/  AcpiOsReleaseMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AcpiUtGetMutexName (size_t) ; 
 int /*<<< orphan*/  UtReleaseMutex ; 

ACPI_STATUS
AcpiUtReleaseMutex (
    ACPI_MUTEX_HANDLE       MutexId)
{
    ACPI_FUNCTION_NAME (UtReleaseMutex);


    ACPI_DEBUG_PRINT ((ACPI_DB_MUTEX, "Thread %u releasing Mutex [%s]\n",
        (UINT32) AcpiOsGetThreadId (), AcpiUtGetMutexName (MutexId)));

    if (MutexId > ACPI_MAX_MUTEX)
    {
        return (AE_BAD_PARAMETER);
    }

    /*
     * Mutex must be acquired in order to release it!
     */
    if (AcpiGbl_MutexInfo[MutexId].ThreadId == ACPI_MUTEX_NOT_ACQUIRED)
    {
        ACPI_ERROR ((AE_INFO,
            "Mutex [%s] (0x%X) is not acquired, cannot release",
            AcpiUtGetMutexName (MutexId), MutexId));

        return (AE_NOT_ACQUIRED);
    }

#ifdef ACPI_MUTEX_DEBUG
    {
        UINT32                  i;
        /*
         * Mutex debug code, for internal debugging only.
         *
         * Deadlock prevention. Check if this thread owns any mutexes of value
         * greater than this one. If so, the thread has violated the mutex
         * ordering rule. This indicates a coding error somewhere in
         * the ACPI subsystem code.
         */
        for (i = MutexId; i < ACPI_NUM_MUTEX; i++)
        {
            if (AcpiGbl_MutexInfo[i].ThreadId == AcpiOsGetThreadId ())
            {
                if (i == MutexId)
                {
                    continue;
                }

                ACPI_ERROR ((AE_INFO,
                    "Invalid release order: owns [%s], releasing [%s]",
                    AcpiUtGetMutexName (i), AcpiUtGetMutexName (MutexId)));

                return (AE_RELEASE_DEADLOCK);
            }
        }
    }
#endif

    /* Mark unlocked FIRST */

    AcpiGbl_MutexInfo[MutexId].ThreadId = ACPI_MUTEX_NOT_ACQUIRED;

    AcpiOsReleaseMutex (AcpiGbl_MutexInfo[MutexId].Mutex);
    return (AE_OK);
}