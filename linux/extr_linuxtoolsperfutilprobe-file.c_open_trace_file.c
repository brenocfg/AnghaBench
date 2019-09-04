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
 int O_APPEND ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int PATH_MAX ; 
 int e_snprintf (char*,int,char*,int /*<<< orphan*/ ,char const*) ; 
 int errno ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,char*,int) ; 
 int /*<<< orphan*/  probe_event_dry_run ; 
 int /*<<< orphan*/  tracing_path_mount () ; 

int open_trace_file(const char *trace_file, bool readwrite)
{
	char buf[PATH_MAX];
	int ret;

	ret = e_snprintf(buf, PATH_MAX, "%s/%s", tracing_path_mount(), trace_file);
	if (ret >= 0) {
		pr_debug("Opening %s write=%d\n", buf, readwrite);
		if (readwrite && !probe_event_dry_run)
			ret = open(buf, O_RDWR | O_APPEND, 0);
		else
			ret = open(buf, O_RDONLY, 0);

		if (ret < 0)
			ret = -errno;
	}
	return ret;
}