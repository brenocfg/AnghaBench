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
typedef  enum bpf_attach_type { ____Placeholder_bpf_attach_type } bpf_attach_type ;

/* Variables and functions */
 int BPF_F_QUERY_EFFECTIVE ; 
 char* GET_ARG () ; 
 int /*<<< orphan*/  NEXT_ARG () ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  REQ_ARGS (int) ; 
 int __MAX_BPF_ATTACH_TYPE ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ is_prefix (char*,char*) ; 
 scalar_t__ json_output ; 
 int /*<<< orphan*/  json_wtr ; 
 int /*<<< orphan*/  jsonw_end_array (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsonw_start_array (int /*<<< orphan*/ ) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_err (char*,char const*) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*) ; 
 int query_flags ; 
 scalar_t__ show_attached_bpf_progs (int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int do_show(int argc, char **argv)
{
	enum bpf_attach_type type;
	const char *path;
	int cgroup_fd;
	int ret = -1;

	query_flags = 0;

	if (!REQ_ARGS(1))
		return -1;
	path = GET_ARG();

	while (argc) {
		if (is_prefix(*argv, "effective")) {
			if (query_flags & BPF_F_QUERY_EFFECTIVE) {
				p_err("duplicated argument: %s", *argv);
				return -1;
			}
			query_flags |= BPF_F_QUERY_EFFECTIVE;
			NEXT_ARG();
		} else {
			p_err("expected no more arguments, 'effective', got: '%s'?",
			      *argv);
			return -1;
		}
	}

	cgroup_fd = open(path, O_RDONLY);
	if (cgroup_fd < 0) {
		p_err("can't open cgroup %s", path);
		goto exit;
	}

	if (json_output)
		jsonw_start_array(json_wtr);
	else
		printf("%-8s %-15s %-15s %-15s\n", "ID", "AttachType",
		       "AttachFlags", "Name");

	for (type = 0; type < __MAX_BPF_ATTACH_TYPE; type++) {
		/*
		 * Not all attach types may be supported, so it's expected,
		 * that some requests will fail.
		 * If we were able to get the show for at least one
		 * attach type, let's return 0.
		 */
		if (show_attached_bpf_progs(cgroup_fd, type, 0) == 0)
			ret = 0;
	}

	if (json_output)
		jsonw_end_array(json_wtr);

	close(cgroup_fd);
exit:
	return ret;
}