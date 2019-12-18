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
 int /*<<< orphan*/  ASSERT (void*) ; 
 int /*<<< orphan*/  DPRINT (char*,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MmUnmapIoSpace (void*,int /*<<< orphan*/ ) ; 

void
AcpiOsUnmapMemory (
    void                    *virt,
    ACPI_SIZE               length)
{
    DPRINT("AcpiOsMapMemory(phys 0x%p  size 0x%X)\n", virt, length);

    ASSERT(virt);

    MmUnmapIoSpace(virt, length);
}