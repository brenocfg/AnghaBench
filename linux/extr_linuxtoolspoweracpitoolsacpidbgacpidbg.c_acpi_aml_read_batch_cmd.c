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
struct circ_buf {char* buf; size_t head; } ;

/* Variables and functions */
 int ACPI_AML_BUF_SIZE ; 
 int acpi_aml_batch_pos ; 
 int circ_space_to_end (struct circ_buf*) ; 
 int /*<<< orphan*/  memcpy (char*,int,int) ; 
 int strlen (int) ; 

__attribute__((used)) static int acpi_aml_read_batch_cmd(int unused, struct circ_buf *crc)
{
	char *p;
	int len;
	int remained = strlen(acpi_aml_batch_pos);

	p = &crc->buf[crc->head];
	len = circ_space_to_end(crc);
	if (len > remained) {
		memcpy(p, acpi_aml_batch_pos, remained);
		acpi_aml_batch_pos += remained;
		len = remained;
	} else {
		memcpy(p, acpi_aml_batch_pos, len);
		acpi_aml_batch_pos += len;
	}
	if (len > 0)
		crc->head = (crc->head + len) & (ACPI_AML_BUF_SIZE - 1);
	return len;
}