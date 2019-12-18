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
 int parse_event_file (struct tep_handle*,char*,unsigned long long,char*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static int read_event_file(struct tep_handle *pevent, char *sys,
			   unsigned long long size)
{
	int ret;
	char *buf;

	buf = malloc(size);
	if (buf == NULL) {
		pr_debug("memory allocation failure\n");
		return -1;
	}

	ret = do_read(buf, size);
	if (ret < 0)
		goto out;

	ret = parse_event_file(pevent, buf, size, sys);
	if (ret < 0)
		pr_debug("error parsing event file.\n");
out:
	free(buf);
	return ret;
}