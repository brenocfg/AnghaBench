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
typedef  scalar_t__ UINT16 ;
typedef  int /*<<< orphan*/  PFAST_MUTEX ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_MUTEX ;

/* Variables and functions */
 scalar_t__ ACPI_DO_NOT_WAIT ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AE_TIME ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  ExAcquireFastMutex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ExTryToAcquireFastMutex (int /*<<< orphan*/ ) ; 

ACPI_STATUS
AcpiOsAcquireMutex(
    ACPI_MUTEX Handle,
    UINT16 Timeout)
{
    if (!Handle)
    {
        DPRINT1("Bad parameter\n");
        return AE_BAD_PARAMETER;
    }

    /* Check what the caller wants us to do */
    if (Timeout == ACPI_DO_NOT_WAIT)
    {
        /* Try to acquire without waiting */
        if (!ExTryToAcquireFastMutex((PFAST_MUTEX)Handle))
            return AE_TIME;
    }
    else
    {
        /* Block until we get it */
        ExAcquireFastMutex((PFAST_MUTEX)Handle);
    }

    return AE_OK;
}