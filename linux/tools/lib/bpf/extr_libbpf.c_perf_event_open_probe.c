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
typedef  int /*<<< orphan*/  uint64_t ;
struct perf_event_attr {int config; int size; int type; int /*<<< orphan*/  config2; int /*<<< orphan*/  config1; } ;
typedef  int /*<<< orphan*/  errmsg ;
typedef  int /*<<< orphan*/  attr ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_FLAG_FD_CLOEXEC ; 
 int STRERR_BUFSIZE ; 
 int /*<<< orphan*/  __NR_perf_event_open ; 
 int determine_kprobe_perf_type () ; 
 int determine_kprobe_retprobe_bit () ; 
 int determine_uprobe_perf_type () ; 
 int determine_uprobe_retprobe_bit () ; 
 int errno ; 
 int /*<<< orphan*/  libbpf_strerror_r (int,char*,int) ; 
 int /*<<< orphan*/  pr_warning (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ptr_to_u64 (char const*) ; 
 int syscall (int /*<<< orphan*/ ,struct perf_event_attr*,int,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int perf_event_open_probe(bool uprobe, bool retprobe, const char *name,
				 uint64_t offset, int pid)
{
	struct perf_event_attr attr = {};
	char errmsg[STRERR_BUFSIZE];
	int type, pfd, err;

	type = uprobe ? determine_uprobe_perf_type()
		      : determine_kprobe_perf_type();
	if (type < 0) {
		pr_warning("failed to determine %s perf type: %s\n",
			   uprobe ? "uprobe" : "kprobe",
			   libbpf_strerror_r(type, errmsg, sizeof(errmsg)));
		return type;
	}
	if (retprobe) {
		int bit = uprobe ? determine_uprobe_retprobe_bit()
				 : determine_kprobe_retprobe_bit();

		if (bit < 0) {
			pr_warning("failed to determine %s retprobe bit: %s\n",
				   uprobe ? "uprobe" : "kprobe",
				   libbpf_strerror_r(bit, errmsg,
						     sizeof(errmsg)));
			return bit;
		}
		attr.config |= 1 << bit;
	}
	attr.size = sizeof(attr);
	attr.type = type;
	attr.config1 = ptr_to_u64(name); /* kprobe_func or uprobe_path */
	attr.config2 = offset;		 /* kprobe_addr or probe_offset */

	/* pid filter is meaningful only for uprobes */
	pfd = syscall(__NR_perf_event_open, &attr,
		      pid < 0 ? -1 : pid /* pid */,
		      pid == -1 ? 0 : -1 /* cpu */,
		      -1 /* group_fd */, PERF_FLAG_FD_CLOEXEC);
	if (pfd < 0) {
		err = -errno;
		pr_warning("%s perf_event_open() failed: %s\n",
			   uprobe ? "uprobe" : "kprobe",
			   libbpf_strerror_r(err, errmsg, sizeof(errmsg)));
		return err;
	}
	return pfd;
}