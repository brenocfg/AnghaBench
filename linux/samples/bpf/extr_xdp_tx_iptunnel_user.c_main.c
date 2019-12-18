#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {unsigned int* v6; } ;
struct vip {unsigned short family; int /*<<< orphan*/  dport; void* protocol; TYPE_1__ daddr; } ;
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_6__ {unsigned int* v6; } ;
struct TYPE_5__ {unsigned int* v6; } ;
struct iptnl_info {unsigned short family; scalar_t__ dmac; TYPE_3__ daddr; TYPE_2__ saddr; } ;
struct ether_addr {int dummy; } ;
struct bpf_prog_load_attr {char* file; int /*<<< orphan*/  prog_type; } ;
struct bpf_prog_info {int /*<<< orphan*/  id; } ;
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  info ;
typedef  int /*<<< orphan*/  filename ;
typedef  int __u32 ;

/* Variables and functions */
 unsigned short AF_UNSPEC ; 
 int /*<<< orphan*/  BPF_NOEXIST ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_XDP ; 
 void* IPPROTO_TCP ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  XDP_FLAGS_DRV_MODE ; 
 int /*<<< orphan*/  XDP_FLAGS_SKB_MODE ; 
 int /*<<< orphan*/  XDP_FLAGS_UPDATE_IF_NOEXIST ; 
 void* atoi (char*) ; 
 scalar_t__ bpf_map_update_elem (int,struct vip*,struct iptnl_info*,int /*<<< orphan*/ ) ; 
 int bpf_obj_get_info_by_fd (int,struct bpf_prog_info*,int*) ; 
 void* bpf_object__find_map_fd_by_name (struct bpf_object*,char*) ; 
 scalar_t__ bpf_prog_load_xattr (struct bpf_prog_load_attr*,struct bpf_object**,int*) ; 
 scalar_t__ bpf_set_link_xdp_fd (void*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  ether_aton_r (char*,struct ether_addr*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int getopt (int,char**,char const*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 void* if_nametoindex (char*) ; 
 void* ifindex ; 
 int /*<<< orphan*/  int_exit ; 
 char* optarg ; 
 void* parse_ipstr (char*,unsigned int*) ; 
 int /*<<< orphan*/  parse_ports (char*,int*,int*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  poll_stats (unsigned int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  prog_id ; 
 scalar_t__ rxcnt_map_fd ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  usage (char*) ; 
 int /*<<< orphan*/  xdp_flags ; 

int main(int argc, char **argv)
{
	struct bpf_prog_load_attr prog_load_attr = {
		.prog_type	= BPF_PROG_TYPE_XDP,
	};
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	int min_port = 0, max_port = 0, vip2tnl_map_fd;
	const char *optstr = "i:a:p:s:d:m:T:P:FSNh";
	unsigned char opt_flags[256] = {};
	struct bpf_prog_info info = {};
	__u32 info_len = sizeof(info);
	unsigned int kill_after_s = 0;
	struct iptnl_info tnl = {};
	struct bpf_object *obj;
	struct vip vip = {};
	char filename[256];
	int opt, prog_fd;
	int i, err;

	tnl.family = AF_UNSPEC;
	vip.protocol = IPPROTO_TCP;

	for (i = 0; i < strlen(optstr); i++)
		if (optstr[i] != 'h' && 'a' <= optstr[i] && optstr[i] <= 'z')
			opt_flags[(unsigned char)optstr[i]] = 1;

	while ((opt = getopt(argc, argv, optstr)) != -1) {
		unsigned short family;
		unsigned int *v6;

		switch (opt) {
		case 'i':
			ifindex = if_nametoindex(optarg);
			if (!ifindex)
				ifindex = atoi(optarg);
			break;
		case 'a':
			vip.family = parse_ipstr(optarg, vip.daddr.v6);
			if (vip.family == AF_UNSPEC)
				return 1;
			break;
		case 'p':
			if (parse_ports(optarg, &min_port, &max_port))
				return 1;
			break;
		case 'P':
			vip.protocol = atoi(optarg);
			break;
		case 's':
		case 'd':
			if (opt == 's')
				v6 = tnl.saddr.v6;
			else
				v6 = tnl.daddr.v6;

			family = parse_ipstr(optarg, v6);
			if (family == AF_UNSPEC)
				return 1;
			if (tnl.family == AF_UNSPEC) {
				tnl.family = family;
			} else if (tnl.family != family) {
				fprintf(stderr,
					"The IP version of the src and dst addresses used in the IP encapsulation does not match\n");
				return 1;
			}
			break;
		case 'm':
			if (!ether_aton_r(optarg,
					  (struct ether_addr *)tnl.dmac)) {
				fprintf(stderr, "Invalid mac address:%s\n",
					optarg);
				return 1;
			}
			break;
		case 'T':
			kill_after_s = atoi(optarg);
			break;
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
			usage(argv[0]);
			return 1;
		}
		opt_flags[opt] = 0;
	}

	for (i = 0; i < strlen(optstr); i++) {
		if (opt_flags[(unsigned int)optstr[i]]) {
			fprintf(stderr, "Missing argument -%c\n", optstr[i]);
			usage(argv[0]);
			return 1;
		}
	}

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK, RLIM_INFINITY)");
		return 1;
	}

	if (!ifindex) {
		fprintf(stderr, "Invalid ifname\n");
		return 1;
	}

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	prog_load_attr.file = filename;

	if (bpf_prog_load_xattr(&prog_load_attr, &obj, &prog_fd))
		return 1;

	if (!prog_fd) {
		printf("load_bpf_file: %s\n", strerror(errno));
		return 1;
	}

	rxcnt_map_fd = bpf_object__find_map_fd_by_name(obj, "rxcnt");
	vip2tnl_map_fd = bpf_object__find_map_fd_by_name(obj, "vip2tnl");
	if (vip2tnl_map_fd < 0 || rxcnt_map_fd < 0) {
		printf("bpf_object__find_map_fd_by_name failed\n");
		return 1;
	}

	signal(SIGINT, int_exit);
	signal(SIGTERM, int_exit);

	while (min_port <= max_port) {
		vip.dport = htons(min_port++);
		if (bpf_map_update_elem(vip2tnl_map_fd, &vip, &tnl,
					BPF_NOEXIST)) {
			perror("bpf_map_update_elem(&vip2tnl)");
			return 1;
		}
	}

	if (bpf_set_link_xdp_fd(ifindex, prog_fd, xdp_flags) < 0) {
		printf("link set xdp fd failed\n");
		return 1;
	}

	err = bpf_obj_get_info_by_fd(prog_fd, &info, &info_len);
	if (err) {
		printf("can't get prog info - %s\n", strerror(errno));
		return err;
	}
	prog_id = info.id;

	poll_stats(kill_after_s);

	bpf_set_link_xdp_fd(ifindex, -1, xdp_flags);

	return 0;
}