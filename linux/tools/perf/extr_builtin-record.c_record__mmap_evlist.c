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
struct record_opts {scalar_t__ affinity; int mmap_pages; int /*<<< orphan*/  auxtrace_mmap_pages; int /*<<< orphan*/  comp_level; int /*<<< orphan*/  mmap_flush; int /*<<< orphan*/  nr_cblocks; int /*<<< orphan*/  auxtrace_snapshot_mode; } ;
struct record {struct record_opts opts; } ;
struct evlist {int dummy; } ;
typedef  int /*<<< orphan*/  msg ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 scalar_t__ PERF_AFFINITY_SYS ; 
 int /*<<< orphan*/  cpu__setup_cpunode_map () ; 
 int errno ; 
 scalar_t__ evlist__mmap_ex (struct evlist*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_error_r (int,char*,int) ; 

__attribute__((used)) static int record__mmap_evlist(struct record *rec,
			       struct evlist *evlist)
{
	struct record_opts *opts = &rec->opts;
	char msg[512];

	if (opts->affinity != PERF_AFFINITY_SYS)
		cpu__setup_cpunode_map();

	if (evlist__mmap_ex(evlist, opts->mmap_pages,
				 opts->auxtrace_mmap_pages,
				 opts->auxtrace_snapshot_mode,
				 opts->nr_cblocks, opts->affinity,
				 opts->mmap_flush, opts->comp_level) < 0) {
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