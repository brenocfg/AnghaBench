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
struct record_opts {int mmap_pages; int /*<<< orphan*/  auxtrace_mmap_pages; int /*<<< orphan*/  auxtrace_snapshot_mode; } ;
struct record {struct record_opts opts; } ;
struct perf_evlist {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int errno ; 
 scalar_t__ perf_evlist__mmap_ex (struct perf_evlist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 

__attribute__((used)) static int record__mmap_evlist(struct record *rec,
			       struct perf_evlist *evlist)
{
	struct record_opts *opts = &rec->opts;
	char msg[512];

	if (perf_evlist__mmap_ex(evlist, opts->mmap_pages,
				 opts->auxtrace_mmap_pages,
				 opts->auxtrace_snapshot_mode) < 0) {
		if (errno == EPERM) {
			pr_err("Permission error mapping pages.\n"
			       "Consider increasing "
			       "/proc/sys/kernel/perf_event_mlock_kb,\n"
			       "or try again with a smaller value of -m/--mmap_pages.\n"
			       "(current value: %u,%u)\n",
			       opts->mmap_pages, opts->auxtrace_mmap_pages);
			return -errno;
		} else {
			pr_err("failed to mmap with %d (%s)\n", errno,
				str_error_r(errno, msg, sizeof(msg)));
			if (errno)
				return -errno;
			else
				return -EINVAL;
		}
	}
	return 0;
}