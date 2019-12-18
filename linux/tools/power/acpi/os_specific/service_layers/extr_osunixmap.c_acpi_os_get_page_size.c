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
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  _SC_PAGESIZE ; 
 int /*<<< orphan*/  sysconf (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_size acpi_os_get_page_size(void)
{

#ifdef PAGE_SIZE
	return PAGE_SIZE;
#else
	return sysconf(_SC_PAGESIZE);
#endif
}