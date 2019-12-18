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
typedef  int /*<<< orphan*/  ACPI_SIZE ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_ENTRY () ; 
 void* AcpiOsAllocate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void *
AcpiOsAllocateZeroed (
    ACPI_SIZE               Size)
{
    void                    *Allocation;


    ACPI_FUNCTION_ENTRY ();


    Allocation = AcpiOsAllocate (Size);
    if (Allocation)
    {
        /* Clear the memory block */

        memset (Allocation, 0, Size);
    }

    return (Allocation);
}