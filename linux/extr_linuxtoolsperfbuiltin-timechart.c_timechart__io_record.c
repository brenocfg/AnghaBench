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
 unsigned int ARRAY_SIZE (char const* const*) ; 
 int ENOMEM ; 
 scalar_t__ asprintf (char**,char*,int /*<<< orphan*/ ) ; 
 char** calloc (unsigned int,int) ; 
 int cmd_record (unsigned int,char const**) ; 
 int /*<<< orphan*/  free (char const**) ; 
 int /*<<< orphan*/  getpid () ; 
 int /*<<< orphan*/  is_valid_tracepoint (char const* const) ; 
 void* strdup (char const* const) ; 

__attribute__((used)) static int timechart__io_record(int argc, const char **argv)
{
	unsigned int rec_argc, i;
	const char **rec_argv;
	const char **p;
	char *filter = NULL;

	const char * const common_args[] = {
		"record", "-a", "-R", "-c", "1",
	};
	unsigned int common_args_nr = ARRAY_SIZE(common_args);

	const char * const disk_events[] = {
		"syscalls:sys_enter_read",
		"syscalls:sys_enter_pread64",
		"syscalls:sys_enter_readv",
		"syscalls:sys_enter_preadv",
		"syscalls:sys_enter_write",
		"syscalls:sys_enter_pwrite64",
		"syscalls:sys_enter_writev",
		"syscalls:sys_enter_pwritev",
		"syscalls:sys_enter_sync",
		"syscalls:sys_enter_sync_file_range",
		"syscalls:sys_enter_fsync",
		"syscalls:sys_enter_msync",

		"syscalls:sys_exit_read",
		"syscalls:sys_exit_pread64",
		"syscalls:sys_exit_readv",
		"syscalls:sys_exit_preadv",
		"syscalls:sys_exit_write",
		"syscalls:sys_exit_pwrite64",
		"syscalls:sys_exit_writev",
		"syscalls:sys_exit_pwritev",
		"syscalls:sys_exit_sync",
		"syscalls:sys_exit_sync_file_range",
		"syscalls:sys_exit_fsync",
		"syscalls:sys_exit_msync",
	};
	unsigned int disk_events_nr = ARRAY_SIZE(disk_events);

	const char * const net_events[] = {
		"syscalls:sys_enter_recvfrom",
		"syscalls:sys_enter_recvmmsg",
		"syscalls:sys_enter_recvmsg",
		"syscalls:sys_enter_sendto",
		"syscalls:sys_enter_sendmsg",
		"syscalls:sys_enter_sendmmsg",

		"syscalls:sys_exit_recvfrom",
		"syscalls:sys_exit_recvmmsg",
		"syscalls:sys_exit_recvmsg",
		"syscalls:sys_exit_sendto",
		"syscalls:sys_exit_sendmsg",
		"syscalls:sys_exit_sendmmsg",
	};
	unsigned int net_events_nr = ARRAY_SIZE(net_events);

	const char * const poll_events[] = {
		"syscalls:sys_enter_epoll_pwait",
		"syscalls:sys_enter_epoll_wait",
		"syscalls:sys_enter_poll",
		"syscalls:sys_enter_ppoll",
		"syscalls:sys_enter_pselect6",
		"syscalls:sys_enter_select",

		"syscalls:sys_exit_epoll_pwait",
		"syscalls:sys_exit_epoll_wait",
		"syscalls:sys_exit_poll",
		"syscalls:sys_exit_ppoll",
		"syscalls:sys_exit_pselect6",
		"syscalls:sys_exit_select",
	};
	unsigned int poll_events_nr = ARRAY_SIZE(poll_events);

	rec_argc = common_args_nr +
		disk_events_nr * 4 +
		net_events_nr * 4 +
		poll_events_nr * 4 +
		argc;
	rec_argv = calloc(rec_argc + 1, sizeof(char *));

	if (rec_argv == NULL)
		return -ENOMEM;

	if (asprintf(&filter, "common_pid != %d", getpid()) < 0) {
		free(rec_argv);
		return -ENOMEM;
	}

	p = rec_argv;
	for (i = 0; i < common_args_nr; i++)
		*p++ = strdup(common_args[i]);

	for (i = 0; i < disk_events_nr; i++) {
		if (!is_valid_tracepoint(disk_events[i])) {
			rec_argc -= 4;
			continue;
		}

		*p++ = "-e";
		*p++ = strdup(disk_events[i]);
		*p++ = "--filter";
		*p++ = filter;
	}
	for (i = 0; i < net_events_nr; i++) {
		if (!is_valid_tracepoint(net_events[i])) {
			rec_argc -= 4;
			continue;
		}

		*p++ = "-e";
		*p++ = strdup(net_events[i]);
		*p++ = "--filter";
		*p++ = filter;
	}
	for (i = 0; i < poll_events_nr; i++) {
		if (!is_valid_tracepoint(poll_events[i])) {
			rec_argc -= 4;
			continue;
		}

		*p++ = "-e";
		*p++ = strdup(poll_events[i]);
		*p++ = "--filter";
		*p++ = filter;
	}

	for (i = 0; i < (unsigned int)argc; i++)
		*p++ = argv[i];

	return cmd_record(rec_argc, rec_argv);
}