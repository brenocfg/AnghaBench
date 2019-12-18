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
struct circ_buf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_AML_BATCH_READ_LOG ; 
 int /*<<< orphan*/  acpi_aml_batch_state ; 
 int acpi_aml_write (int,struct circ_buf*) ; 
 scalar_t__ circ_count_to_end (struct circ_buf*) ; 

__attribute__((used)) static int acpi_aml_write_batch_cmd(int fd, struct circ_buf *crc)
{
	int len;

	len = acpi_aml_write(fd, crc);
	if (circ_count_to_end(crc) == 0)
		acpi_aml_batch_state = ACPI_AML_BATCH_READ_LOG;
	return len;
}