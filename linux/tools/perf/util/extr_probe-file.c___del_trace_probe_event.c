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
struct str_node {char* s; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ENOTSUP ; 
 int e_snprintf (char*,int,char*,char*) ; 
 int errno ; 
 int /*<<< orphan*/  pr_debug (char*,char*) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int write (int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __del_trace_probe_event(int fd, struct str_node *ent)
{
	char *p;
	char buf[128];
	int ret;

	/* Convert from perf-probe event to trace-probe event */
	ret = e_snprintf(buf, 128, "-:%s", ent->s);
	if (ret < 0)
		goto error;

	p = strchr(buf + 2, ':');
	if (!p) {
		pr_debug("Internal error: %s should have ':' but not.\n",
			 ent->s);
		ret = -ENOTSUP;
		goto error;
	}
	*p = '/';

	pr_debug("Writing event: %s\n", buf);
	ret = write(fd, buf, strlen(buf));
	if (ret < 0) {
		ret = -errno;
		goto error;
	}

	return 0;
error:
	pr_warning("Failed to delete event: %s\n",
		   str_error_r(-ret, buf, sizeof(buf)));
	return ret;
}