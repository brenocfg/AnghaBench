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
struct bpf_prog_load_attr {char* file; int /*<<< orphan*/  expected_attach_type; int /*<<< orphan*/  prog_type; } ;
struct bpf_map {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_CGROUP_INET_EGRESS ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_CGROUP_SKB ; 
 int /*<<< orphan*/  O_RDONLY ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 char* bpf_log_buf ; 
 int bpf_map__fd (struct bpf_map*) ; 
 struct bpf_map* bpf_object__find_map_by_name (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ bpf_prog_load_xattr (struct bpf_prog_load_attr*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bpfprog_fd ; 
 int errno ; 
 int /*<<< orphan*/  obj ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 char* strerror (int) ; 

__attribute__((used)) static int prog_load(char *prog)
{
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type = BPF_PROG_TYPE_CGROUP_SKB,
		.file = prog,
		.expected_attach_type = BPF_CGROUP_INET_EGRESS,
	};
	int map_fd;
	struct bpf_map *map;

	int ret = 0;

	if (access(prog, O_RDONLY) < 0) {
		printf("Error accessing file %s: %s\n", prog, strerror(errno));
		return 1;
	}
	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &bpfprog_fd))
		ret = 1;
	if (!ret) {
		map = bpf_object__find_map_by_name(obj, "queue_stats");
		map_fd = bpf_map__fd(map);
		if (map_fd < 0) {
			printf("Map not found: %s\n", strerror(map_fd));
			ret = 1;
		}
	}

	if (ret) {
		printf("ERROR: load_bpf_file failed for: %s\n", prog);
		printf("  Output from verifier:\n%s\n------\n", bpf_log_buf);
		ret = -1;
	} else {
		ret = map_fd;
	}

	return ret;
}