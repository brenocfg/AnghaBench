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
struct bpf_program {int dummy; } ;
struct bpf_prog_load_attr {char* file; int /*<<< orphan*/  prog_type; } ;
struct bpf_prog_info {int /*<<< orphan*/  id; } ;
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  filename ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_XDP ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int XDP_FLAGS_DRV_MODE ; 
 int XDP_FLAGS_SKB_MODE ; 
 int XDP_FLAGS_UPDATE_IF_NOEXIST ; 
 int /*<<< orphan*/  basename (char*) ; 
 int bpf_map_update_elem (int,int*,int*,int /*<<< orphan*/ ) ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 void* bpf_object__find_map_fd_by_name (struct bpf_object*,char*) ; 
 scalar_t__ bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 int bpf_program__fd (struct bpf_program*) ; 
 struct bpf_program* bpf_program__next (struct bpf_program*,struct bpf_object*) ; 
 scalar_t__ bpf_set_link_xdp_fd (int,int,int) ; 
 int /*<<< orphan*/  dummy_prog_id ; 
 int /*<<< orphan*/  errno ; 
 int getopt (int,char**,char const*) ; 
 int if_nametoindex (char*) ; 
 int ifindex_in ; 
 int ifindex_out ; 
 int ifindex_out_xdp_dummy_attached ; 
 int /*<<< orphan*/  int_exit ; 
 int /*<<< orphan*/  memset (struct bpf_prog_info*,int /*<<< orphan*/ ,int) ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poll_stats (int,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prog_id ; 
 void* rxcnt_map_fd ; 
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
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type	= BPF_PROG_TYPE_XDP,
	};
	struct bpf_program *prog, *dummy_prog;
	struct bpf_prog_info info = {};
	__u32 info_len = sizeof(info);
	int prog_fd, dummy_prog_fd;
	const char *optstr = "FSN";
	struct bpf_object *obj;
	int ret, opt, key = 0;
	char filename[256];
	int tx_port_map_fd;

	while ((opt = getopt(argc, argv, optstr)) != -1) {
		switch (opt) {
		case 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			break;
		case 'N':
			xdp_flags |= XDP_FLAGS_DRV_MODE;
			break;
		case 'F':
			xdp_flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			break;
		default:
			usage(basename(argv[0]));
			return 1;
		}
	}

	if (optind == argc) {
		printf("usage: %s <IFNAME|IFINDEX>_IN <IFNAME|IFINDEX>_OUT\n", argv[0]);
		return 1;
	}

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return 1;
	}

	ifindex_in = if_nametoindex(argv[optind]);
	if (!ifindex_in)
		ifindex_in = strtoul(argv[optind], NULL, 0);

	ifindex_out = if_nametoindex(argv[optind + 1]);
	if (!ifindex_out)
		ifindex_out = strtoul(argv[optind + 1], NULL, 0);

	printf("input: %d output: %d\n", ifindex_in, ifindex_out);

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return 1;

	prog = bpf_program__next(NULL, obj);
	dummy_prog = bpf_program__next(prog, obj);
	if (!prog || !dummy_prog) {
		printf("finding a prog in obj file failed\n");
		return 1;
	}
	/* bpf_prog_load_xattr gives us the pointer to first prog's fd,
	 * so we're missing only the fd for dummy prog
	 */
	dummy_prog_fd = bpf_program__fd(dummy_prog);
	if (prog_fd < 0 || dummy_prog_fd < 0) {
		printf("bpf_prog_load_xattr: %s\n", strerror(errno));
		return 1;
	}

	tx_port_map_fd = bpf_object__find_map_fd_by_name(obj, "tx_port");
	rxcnt_map_fd = bpf_object__find_map_fd_by_name(obj, "rxcnt");
	if (tx_port_map_fd < 0 || rxcnt_map_fd < 0) {
		printf("bpf_object__find_map_fd_by_name failed\n");
		return 1;
	}

	if (bpf_set_link_xdp_fd(ifindex_in, prog_fd, xdp_flags) < 0) {
		printf("ERROR: link set xdp fd failed on %d\n", ifindex_in);
		return 1;
	}

	ret = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	if (ret) {
		printf("can't get prog info - %s\n", strerror(errno));
		return ret;
	}
	prog_id = info.id;

	/* Loading dummy XDP prog on out-device */
	if (bpf_set_link_xdp_fd(ifindex_out, dummy_prog_fd,
			    (xdp_flags | XDP_FLAGS_UPDATE_IF_NOEXIST)) < 0) {
		printf("WARN: link set xdp fd failed on %d\n", ifindex_out);
		ifindex_out_xdp_dummy_attached = false;
	}

	memset(&info, 0, sizeof(info));
	ret = bpf_obj_get_info_by_fd(dummy_prog_fd, &info, &info_len);
	if (ret) {
		printf("can't get prog info - %s\n", strerror(errno));
		return ret;
	}
	dummy_prog_id = info.id;

	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	/* populate virtual to physical port map */
	ret = bpf_map_update_elem(tx_port_map_fd, &key, &ifindex_out, 0);
	if (ret) {
		perror("bpf_update_elem");
		goto out;
	}

	poll_stats(2, ifindex_out);

out:
	return 0;
}