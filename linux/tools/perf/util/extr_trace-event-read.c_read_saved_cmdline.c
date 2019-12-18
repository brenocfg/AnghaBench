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
 int do_read (char*,unsigned long long) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (unsigned long long) ; 
 int /*<<< orphan*/  parse_saved_cmdline (struct tep_handle*,char*,unsigned long long) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 unsigned long long read8 (struct tep_handle*) ; 

__attribute__((used)) static int read_saved_cmdline(struct tep_handle *pevent)
{
	unsigned long long size;
	char *buf;
	int ret;

	/* it can have 0 size */
	size = read8(pevent);
	if (!size)
		return 0;

	buf = malloc(size + 1);
	if (buf == NULL) {
		pr_debug("memory allocation failure\n");
		return -1;
	}

	ret = do_read(buf, size);
	if (ret < 0) {
		pr_debug("error reading saved cmdlines\n");
		goto out;
	}

	parse_saved_cmdline(pevent, buf, size);
	ret = 0;
out:
	free(buf);
	return ret;
}