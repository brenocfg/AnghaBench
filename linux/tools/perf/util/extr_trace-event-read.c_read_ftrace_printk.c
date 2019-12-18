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
struct tep_handle {int dummy; } ;

/* Variables and functions */
 scalar_t__ do_read (char*,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (unsigned int) ; 
 int /*<<< orphan*/  parse_ftrace_printk (struct tep_handle*,char*,unsigned int) ; 
 unsigned int read4 (struct tep_handle*) ; 

__attribute__((used)) static int read_ftrace_printk(struct tep_handle *pevent)
{
	unsigned int size;
	char *buf;

	/* it can have 0 size */
	size = read4(pevent);
	if (!size)
		return 0;

	buf = malloc(size + 1);
	if (buf == NULL)
		return -1;

	if (do_read(buf, size) < 0) {
		free(buf);
		return -1;
	}

	buf[size] = '\0';

	parse_ftrace_printk(pevent, buf, size);

	free(buf);
	return 0;
}