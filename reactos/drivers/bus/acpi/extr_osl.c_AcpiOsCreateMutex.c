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
typedef  scalar_t__ PFAST_MUTEX ;
typedef  int /*<<< orphan*/  FAST_MUTEX ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_MUTEX ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  ExInitializeFastMutex (scalar_t__) ; 
 int /*<<< orphan*/  NonPagedPool ; 

ACPI_STATUS
AcpiOsCreateMutex(
    ACPI_MUTEX *OutHandle)
{
    PFAST_MUTEX Mutex;

    if (!OutHandle)
    {
        DPRINT1("Bad parameter\n");
        return AE_BAD_PARAMETER;
    }

    Mutex = ExAllocatePoolWithTag(NonPagedPool, sizeof(FAST_MUTEX), 'LpcA');
    if (!Mutex) return AE_NO_MEMORY;

    ExInitializeFastMutex(Mutex);

    *OutHandle = (ACPI_MUTEX)Mutex;

    return AE_OK;
}