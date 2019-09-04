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
typedef  int /*<<< orphan*/  u8 ;
typedef  int acpi_size ;
typedef  int acpi_physical_address ;

/* Variables and functions */
 int ACPI_TO_INTEGER (void*) ; 
 int acpi_os_get_page_size () ; 
 int /*<<< orphan*/  munmap (int /*<<< orphan*/ *,int) ; 

void acpi_os_unmap_memory(void *where, acpi_size length)
{
	acpi_physical_address offset;
	acpi_size page_size;

	page_size = acpi_os_get_page_size();
	offset = ACPI_TO_INTEGER(where) % page_size;
	munmap((u8 *)where - offset, (length + offset));
}