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
struct TYPE_2__ {scalar_t__ UseCount; int /*<<< orphan*/  ThreadId; int /*<<< orphan*/  Mutex; } ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  size_t ACPI_MUTEX_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_U32 (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ACPI_MUTEX_NOT_ACQUIRED ; 
 int /*<<< orphan*/  AE_OK ; 
 TYPE_1__* AcpiGbl_MutexInfo ; 
 int /*<<< orphan*/  AcpiOsCreateMutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  UtCreateMutex ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ACPI_STATUS
AcpiUtCreateMutex (
    ACPI_MUTEX_HANDLE       MutexId)
{
    ACPI_STATUS             Status = AE_OK;


    ACPI_FUNCTION_TRACE_U32 (UtCreateMutex, MutexId);


    if (!AcpiGbl_MutexInfo[MutexId].Mutex)
    {
        Status = AcpiOsCreateMutex (&AcpiGbl_MutexInfo[MutexId].Mutex);
        AcpiGbl_MutexInfo[MutexId].ThreadId = ACPI_MUTEX_NOT_ACQUIRED;
        AcpiGbl_MutexInfo[MutexId].UseCount = 0;
    }

    return_ACPI_STATUS (Status);
}