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
struct perf_event_attr {int size; int config; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  errmsg ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_FLAG_FD_CLOEXEC ; 
 int /*<<< orphan*/  PERF_TYPE_TRACEPOINT ; 
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  __NR_perf_event_open ; 
 int determine_tracepoint_id (char const*,char const*) ; 
 int errno ; 
 int /*<<< orphan*/  libbpf_strerror_r (int,char*,int) ; 
 int /*<<< orphan*/  pr_warning (char*,char const*,char const*,int /*<<< orphan*/ ) ; 
 int syscall (int /*<<< orphan*/ ,struct perf_event_attr*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_event_open_tracepoint(const char *tp_category,
				      const char *tp_name)
{
	struct perf_event_attr attr = {};
	char errmsg[STRERR_BUFSIZE];
	int tp_id, pfd, err;

	tp_id = determine_tracepoint_id(tp_category, tp_name);
	if (tp_id < 0) {
		pr_warning("failed to determine tracepoint '%s/%s' perf event ID: %s\n",
			   tp_category, tp_name,
			   libbpf_strerror_r(tp_id, errmsg, sizeof(errmsg)));
		return tp_id;
	}

	attr.type = PERF_TYPE_TRACEPOINT;
	attr.size = sizeof(attr);
	attr.config = tp_id;

	pfd = syscall(__NR_perf_event_open, &attr, -1 /* pid */, 0 /* cpu */,
		      -1 /* group_fd */, PERF_FLAG_FD_CLOEXEC);
	if (pfd < 0) {
		err = -errno;
		pr_warning("tracepoint '%s/%s' perf_event_open() failed: %s\n",
			   tp_category, tp_name,
			   libbpf_strerror_r(err, errmsg, sizeof(errmsg)));
		return err;
	}
	return pfd;
}