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

/* Variables and functions */
 int acpi_aml_batch_drain ; 
 int /*<<< orphan*/  acpi_aml_loop (int) ; 
 scalar_t__ acpi_aml_readable (int) ; 

__attribute__((used)) static void acpi_aml_flush(int fd)
{
	while (acpi_aml_readable(fd)) {
		acpi_aml_batch_drain = true;
		acpi_aml_loop(fd);
		acpi_aml_batch_drain = false;
	}
}