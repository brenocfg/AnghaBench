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
struct probe_trace_event {int dummy; } ;
typedef  int /*<<< orphan*/  sbuf ;

/* Variables and functions */
 int EINVAL ; 
 int STRERR_BUFSIZE ; 
 int errno ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  pr_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_event_dry_run ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 
 scalar_t__ strlen (char*) ; 
 char* synthesize_probe_trace_command (struct probe_trace_event*) ; 
 int write (int,char*,scalar_t__) ; 

int probe_file__add_event(int fd, struct probe_trace_event *tev)
{
	int ret = 0;
	char *buf = synthesize_probe_trace_command(tev);
	char sbuf[STRERR_BUFSIZE];

	if (!buf) {
		pr_debug("Failed to synthesize probe trace event.\n");
		return -EINVAL;
	}

	pr_debug("Writing event: %s\n", buf);
	if (!probe_event_dry_run) {
		if (write(fd, buf, strlen(buf)) < (int)strlen(buf)) {
			ret = -errno;
			pr_warning("Failed to write event: %s\n",
				   str_error_r(errno, sbuf, sizeof(sbuf)));
		}
	}
	free(buf);

	return ret;
}