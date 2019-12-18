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
struct bpf_prog_load_attr {char* file; int /*<<< orphan*/  prog_type; } ;
struct bpf_prog_info {int id; } ;
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  filename ;
typedef  int __u32 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_XDP ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  XDP_FLAGS_SKB_MODE ; 
 int /*<<< orphan*/  XDP_FLAGS_UPDATE_IF_NOEXIST ; 
 scalar_t__ arp_table_map_fd ; 
 int /*<<< orphan*/  basename (char*) ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 scalar_t__ bpf_object__find_map_fd_by_name (struct bpf_object*,char*) ; 
 scalar_t__ bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 scalar_t__ bpf_set_link_xdp_fd (int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ exact_match_map_fd ; 
 int /*<<< orphan*/  flags ; 
 int /*<<< orphan*/  get_arp_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_route_table (int /*<<< orphan*/ ) ; 
 int getopt (int,char**,char const*) ; 
 int if_nametoindex (char*) ; 
 int* ifindex_list ; 
 int /*<<< orphan*/  int_exit ; 
 scalar_t__ lpm_map_fd ; 
 int /*<<< orphan*/  memset (struct bpf_prog_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ monitor_route () ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* prog_id_list ; 
 scalar_t__ rxcnt_map_fd ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int total_ifindex ; 
 scalar_t__ tx_port_map_fd ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ) ; 

int main(int ac, char **argv)
{
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type	= BPF_PROG_TYPE_XDP,
	};
	struct bpf_prog_info info = {};
	__u32 info_len = sizeof(info);
	const char *optstr = "SF";
	struct bpf_object *obj;
	char filename[256];
	char **ifname_list;
	int prog_fd, opt;
	int err, i = 1;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	total_ifindex = ac - 1;
	ifname_list = (argv + 1);

	while ((opt = getopt(ac, argv, optstr)) != -1) {
		switch (opt) {
		case 'S':
			flags |= XDP_FLAGS_SKB_MODE;
			total_ifindex--;
			ifname_list++;
			break;
		case 'F':
			flags &= ~XDP_FLAGS_UPDATE_IF_NOEXIST;
			total_ifindex--;
			ifname_list++;
			break;
		default:
			usage(basename(argv[0]));
			return 1;
		}
	}

	if (optind == ac) {
		usage(basename(argv[0]));
		return 1;
	}

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return 1;
	}

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return 1;

	printf("\n**************loading bpf file*********************\n\n\n");
	if (!prog_fd) {
		printf("bpf_prog_load_xattr: %s\n", strerror(errno));
		return 1;
	}

	lpm_map_fd = bpf_object__find_map_fd_by_name(obj, "lpm_map");
	rxcnt_map_fd = bpf_object__find_map_fd_by_name(obj, "rxcnt");
	arp_table_map_fd = bpf_object__find_map_fd_by_name(obj, "arp_table");
	exact_match_map_fd = bpf_object__find_map_fd_by_name(obj,
							     "exact_match");
	tx_port_map_fd = bpf_object__find_map_fd_by_name(obj, "tx_port");
	if (lpm_map_fd < 0 || rxcnt_map_fd < 0 || arp_table_map_fd < 0 ||
	    exact_match_map_fd < 0 || tx_port_map_fd < 0) {
		printf("bpf_object__find_map_fd_by_name failed\n");
		return 1;
	}

	ifindex_list = (int *)calloc(total_ifindex, sizeof(int *));
	for (i = 0; i < total_ifindex; i++) {
		ifindex_list[i] = if_nametoindex(ifname_list[i]);
		if (!ifindex_list[i]) {
			printf("Couldn't translate interface name: %s",
			       strerror(errno));
			return 1;
		}
	}
	prog_id_list = (__u32 *)calloc(total_ifindex, sizeof(__u32 *));
	for (i = 0; i < total_ifindex; i++) {
		if (bpf_set_link_xdp_fd(ifindex_list[i], prog_fd, flags) < 0) {
			printf("link set xdp fd failed\n");
			int recovery_index = i;

			for (i = 0; i < recovery_index; i++)
				bpf_set_link_xdp_fd(ifindex_list[i], -1, flags);

			return 1;
		}
		err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
		if (err) {
			printf("can't get prog info - %s\n", strerror(errno));
			return err;
		}
		prog_id_list[i] = info.id;
		memset(&info, 0, sizeof(info));
		printf("Attached to %d\n", ifindex_list[i]);
	}
	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	printf("*******************ROUTE TABLE*************************\n\n\n");
	get_route_table(AF_INET);
	printf("*******************ARP TABLE***************************\n\n\n");
	get_arp_table(AF_INET);
	if (monitor_route() < 0) {
		printf("Error in receiving route update");
		return 1;
	}

	return 0;
}