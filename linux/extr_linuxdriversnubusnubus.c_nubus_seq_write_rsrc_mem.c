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
struct seq_file {int dummy; } ;
struct nubus_dirent {int /*<<< orphan*/  mask; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (unsigned long*) ; 
 unsigned char* nubus_dirptr (struct nubus_dirent const*) ; 
 unsigned long nubus_get_rom (unsigned char**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,unsigned long) ; 
 int /*<<< orphan*/  seq_write (struct seq_file*,unsigned long*,unsigned int) ; 

void nubus_seq_write_rsrc_mem(struct seq_file *m,
			      const struct nubus_dirent *dirent,
			      unsigned int len)
{
	unsigned long buf[32];
	unsigned int buf_size = sizeof(buf);
	unsigned char *p = nubus_dirptr(dirent);

	/* If possible, write out full buffers */
	while (len >= buf_size) {
		unsigned int i;

		for (i = 0; i < ARRAY_SIZE(buf); i++)
			buf[i] = nubus_get_rom(&p, sizeof(buf[0]),
					       dirent->mask);
		seq_write(m, buf, buf_size);
		len -= buf_size;
	}
	/* If not, write out individual bytes */
	while (len--)
		seq_putc(m, nubus_get_rom(&p, 1, dirent->mask));
}