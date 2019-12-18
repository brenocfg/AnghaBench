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
 int circ_space_to_end (struct circ_buf*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int read (int,char*,int) ; 

__attribute__((used)) static int acpi_aml_read(int fd, struct circ_buf *crc)
{
	char *p;
	int len;

	p = &crc->buf[crc->head];
	len = circ_space_to_end(crc);
	len = read(fd, p, len);
	if (len < 0)
		perror("read");
	else if (len > 0)
		crc->head = (crc->head + len) & (ACPI_AML_BUF_SIZE - 1);
	return len;
}