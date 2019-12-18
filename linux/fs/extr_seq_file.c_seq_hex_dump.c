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
struct seq_file {int dummy; } ;

/* Variables and functions */
#define  DUMP_PREFIX_ADDRESS 129 
#define  DUMP_PREFIX_OFFSET 128 
 int hex_dump_to_buffer (int /*<<< orphan*/  const*,int,int,int,char*,size_t,int) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  seq_commit (struct seq_file*,int) ; 
 size_t seq_get_buf (struct seq_file*,char**) ; 
 int /*<<< orphan*/  seq_has_overflowed (struct seq_file*) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char const*,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 

void seq_hex_dump(struct seq_file *m, const char *prefix_str, int prefix_type,
		  int rowsize, int groupsize, const void *buf, size_t len,
		  bool ascii)
{
	const u8 *ptr = buf;
	int i, linelen, remaining = len;
	char *buffer;
	size_t size;
	int ret;

	if (rowsize != 16 && rowsize != 32)
		rowsize = 16;

	for (i = 0; i < len && !seq_has_overflowed(m); i += rowsize) {
		linelen = min(remaining, rowsize);
		remaining -= rowsize;

		switch (prefix_type) {
		case DUMP_PREFIX_ADDRESS:
			seq_printf(m, "%s%p: ", prefix_str, ptr + i);
			break;
		case DUMP_PREFIX_OFFSET:
			seq_printf(m, "%s%.8x: ", prefix_str, i);
			break;
		default:
			seq_printf(m, "%s", prefix_str);
			break;
		}

		size = seq_get_buf(m, &buffer);
		ret = hex_dump_to_buffer(ptr + i, linelen, rowsize, groupsize,
					 buffer, size, ascii);
		seq_commit(m, ret < size ? ret : -1);

		seq_putc(m, '\n');
	}
}