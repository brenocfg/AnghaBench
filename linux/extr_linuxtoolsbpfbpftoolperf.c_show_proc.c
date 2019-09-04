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
struct stat {int dummy; } ;
struct FTW {int dummy; } ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  __u64 ;
typedef  int __u32 ;

/* Variables and functions */
 int FTW_SKIP_SUBTREE ; 
 int bpf_task_fd_query (int,int,int /*<<< orphan*/ ,char*,int*,int*,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ isdigit (char const) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  print_perf_json (int,int,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_perf_plain (int,int,int,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 

__attribute__((used)) static int show_proc(const char *fpath, const struct stat *sb,
		     int tflag, struct FTW *ftwbuf)
{
	__u64 probe_offset, probe_addr;
	__u32 len, prog_id, fd_type;
	int err, pid = 0, fd = 0;
	const char *pch;
	char buf[4096];

	/* prefix always /proc */
	pch = fpath + 5;
	if (*pch == '\0')
		return 0;

	/* pid should be all numbers */
	pch++;
	while (isdigit(*pch)) {
		pid = pid * 10 + *pch - '0';
		pch++;
	}
	if (*pch == '\0')
		return 0;
	if (*pch != '/')
		return FTW_SKIP_SUBTREE;

	/* check /proc/<pid>/fd directory */
	pch++;
	if (strncmp(pch, "fd", 2))
		return FTW_SKIP_SUBTREE;
	pch += 2;
	if (*pch == '\0')
		return 0;
	if (*pch != '/')
		return FTW_SKIP_SUBTREE;

	/* check /proc/<pid>/fd/<fd_num> */
	pch++;
	while (isdigit(*pch)) {
		fd = fd * 10 + *pch - '0';
		pch++;
	}
	if (*pch != '\0')
		return FTW_SKIP_SUBTREE;

	/* query (pid, fd) for potential perf events */
	len = sizeof(buf);
	err = bpf_task_fd_query(pid, fd, 0, buf, &len, &prog_id, &fd_type,
				&probe_offset, &probe_addr);
	if (err < 0)
		return 0;

	if (json_output)
		print_perf_json(pid, fd, prog_id, fd_type, buf, probe_offset,
				probe_addr);
	else
		print_perf_plain(pid, fd, prog_id, fd_type, buf, probe_offset,
				 probe_addr);

	return 0;
}