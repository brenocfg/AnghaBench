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
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int XDP_FLAGS_DRV_MODE ; 
 int XDP_FLAGS_SKB_MODE ; 
 int XDP_FLAGS_UPDATE_IF_NOEXIST ; 
 int /*<<< orphan*/  basename (char*) ; 
 char* bpf_log_buf ; 
 int bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ bpf_set_link_xdp_fd (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  errno ; 
 int getopt (int,char**,char const*) ; 
 int ifindex_in ; 
 int ifindex_out ; 
 int ifindex_out_xdp_dummy_attached ; 
 int /*<<< orphan*/  int_exit ; 
 scalar_t__ load_bpf_file (char*) ; 
 int* map_fd ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poll_stats (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/ * prog_fd ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 
 int xdp_flags ; 

int main(int argc, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	const char *optstr = "SN";
	char filename[256];
	int ret, opt, key = 0;

	while ((opt = getopt(argc, argv, optstr)) != -1) {
		switch (opt) {
		case 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			break;
		case 'N':
			xdp_flags |= XDP_FLAGS_DRV_MODE;
			break;
		default:
			usage(basename(argv[0]));
			return 1;
		}
	}

	if (optind == argc) {
		printf("usage: %s IFINDEX_IN IFINDEX_OUT\n", argv[0]);
		return 1;
	}

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return 1;
	}

	ifindex_in = strtoul(argv[optind], NULL, 0);
	ifindex_out = strtoul(argv[optind + 1], NULL, 0);
	printf("input: %d output: %d\n", ifindex_in, ifindex_out);

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}

	if (!prog_fd[0]) {
		printf("load_bpf_file: %s\n", strerror(errno));
		return 1;
	}

	if (bpf_set_link_xdp_fd(ifindex_in, prog_fd[0], xdp_flags) < 0) {
		printf("ERROR: link set xdp fd failed on %d\n", ifindex_in);
		return 1;
	}

	/* Loading dummy XDP prog on out-device */
	if (bpf_set_link_xdp_fd(ifindex_out, prog_fd[1],
			    (xdp_flags | XDP_FLAGS_UPDATE_IF_NOEXIST)) < 0) {
		printf("WARN: link set xdp fd failed on %d\n", ifindex_out);
		ifindex_out_xdp_dummy_attached = false;
	}

	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	printf("map[0] (vports) = %i, map[1] (map) = %i, map[2] (count) = %i\n",
		map_fd[0], map_fd[1], map_fd[2]);

	/* populate virtual to physical port map */
	ret = bpf_map_update_elem(map_fd[0], &key, &ifindex_out, 0);
	if (ret) {
		perror("bpf_update_elem");
		goto out;
	}

	poll_stats(2, ifindex_out);

out:
	return 0;
}