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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  bpf_task_fd_query (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,char*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  getpid () ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,int /*<<< orphan*/ ) ; 
 int perf_query_supported ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strerror (int) ; 

__attribute__((used)) static bool has_perf_query_support(void)
{
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	char buf[256];
	int fd;

	if (perf_query_supported)
		goto out;

	fd = open("/", O_RDONLY);
	if (fd < 0) {
		p_err("perf_query_support: cannot open directory \"/\" (%s)",
		      strerror(errno));
		goto out;
	}

	/* the following query will fail as no bpf attachment,
	 * the expected errno is ENOTSUPP
	 */
	errno = 0;
	len = sizeof(buf);
	bpf_task_fd_query(getpid(), fd, 0, buf, &len, &prog_id,
			  &fd_type, &probe_offset, &probe_addr);

	if (errno == 524 /* ENOTSUPP */) {
		perf_query_supported = 1;
		goto close_fd;
	}

	perf_query_supported = 2;
	p_err("perf_query_support: %s", strerror(errno));
	fprintf(stderr,
		"HINT: non root or kernel doesn't support TASK_FD_QUERY\n");

close_fd:
	close(fd);
out:
	return perf_query_supported == 1;
}