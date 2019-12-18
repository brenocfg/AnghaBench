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
typedef  scalar_t__ PKSPIN_LOCK ;
typedef  int /*<<< orphan*/  KSPIN_LOCK ;
typedef  int /*<<< orphan*/  ACPI_STATUS ;
typedef  scalar_t__ ACPI_SPINLOCK ;

/* Variables and functions */
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 scalar_t__ ExAllocatePoolWithTag (int /*<<< orphan*/ ,int,char) ; 
 int /*<<< orphan*/  KeInitializeSpinLock (scalar_t__) ; 
 int /*<<< orphan*/  NonPagedPool ; 

ACPI_STATUS
AcpiOsCreateLock(
    ACPI_SPINLOCK *OutHandle)
{
    PKSPIN_LOCK SpinLock;

    if (!OutHandle)
    {
        DPRINT1("Bad parameter\n");
        return AE_BAD_PARAMETER;
    }

    SpinLock = ExAllocatePoolWithTag(NonPagedPool, sizeof(KSPIN_LOCK), 'LpcA');
    if (!SpinLock) return AE_NO_MEMORY;

    KeInitializeSpinLock(SpinLock);

    *OutHandle = (ACPI_SPINLOCK)SpinLock;

    return AE_OK;
}