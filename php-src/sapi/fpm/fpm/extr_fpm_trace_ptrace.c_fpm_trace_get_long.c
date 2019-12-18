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
struct ptrace_io_desc {void* piod_offs; void* piod_addr; int piod_len; int /*<<< orphan*/  piod_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIOD_READ_D ; 
 int /*<<< orphan*/  PTRACE_PEEKDATA ; 
 int /*<<< orphan*/  PT_IO ; 
 int /*<<< orphan*/  ZLOG_SYSERROR ; 
 scalar_t__ errno ; 
 scalar_t__ ptrace (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traced_pid ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int fpm_trace_get_long(long addr, long *data) /* {{{ */
{
#ifdef PT_IO
	struct ptrace_io_desc ptio = {
		.piod_op = PIOD_READ_D,
		.piod_offs = (void *) addr,
		.piod_addr = (void *) data,
		.piod_len = sizeof(long)
	};

	if (0 > ptrace(PT_IO, traced_pid, (void *) &ptio, 0)) {
		zlog(ZLOG_SYSERROR, "failed to ptrace(PT_IO) pid %d", traced_pid);
		return -1;
	}
#else
	errno = 0;
	*data = ptrace(PTRACE_PEEKDATA, traced_pid, (void *) addr, 0);
	if (errno) {
		zlog(ZLOG_SYSERROR, "failed to ptrace(PEEKDATA) pid %d", traced_pid);
		return -1;
	}
#endif
	return 0;
}