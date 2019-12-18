#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; } ;
struct rlimit {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct pinginfo {int count; int /*<<< orphan*/  seq; int /*<<< orphan*/  member_0; } ;
struct bpf_program {int dummy; } ;
struct bpf_object {int dummy; } ;
struct bpf_map {int dummy; } ;
struct addrinfo {int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  rin ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  cmd ;
typedef  int __u32 ;
typedef  int __u16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  BPF_ANY ; 
 int /*<<< orphan*/  BPF_PROG_TYPE_XDP ; 
 int /*<<< orphan*/  RLIMIT_MEMLOCK ; 
 int /*<<< orphan*/  RLIM_INFINITY ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int XDPING_DEFAULT_COUNT ; 
 int XDPING_MAX_COUNT ; 
 int XDP_FLAGS_DRV_MODE ; 
 int XDP_FLAGS_SKB_MODE ; 
 int atoi (char*) ; 
 int /*<<< orphan*/  basename (char*) ; 
 int bpf_map__fd (struct bpf_map*) ; 
 struct bpf_map* bpf_map__next (int /*<<< orphan*/ *,struct bpf_object*) ; 
 scalar_t__ bpf_map_update_elem (int,int*,struct pinginfo*,int /*<<< orphan*/ ) ; 
 struct bpf_program* bpf_object__find_program_by_title (struct bpf_object*,char*) ; 
 scalar_t__ bpf_prog_load (char*,int /*<<< orphan*/ ,struct bpf_object**,int*) ; 
 int bpf_program__fd (struct bpf_program*) ; 
 scalar_t__ bpf_set_link_xdp_fd (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  cleanup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int get_stats (int,int,int) ; 
 scalar_t__ getaddrinfo (char*,int /*<<< orphan*/ *,struct addrinfo*,struct addrinfo**) ; 
 int getopt (int,char**,char const*) ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  if_nametoindex (char*) ; 
 int /*<<< orphan*/  ifindex ; 
 int /*<<< orphan*/  memcpy (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 char* optarg ; 
 int optind ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 scalar_t__ setrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 int /*<<< orphan*/  show_usage (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 int /*<<< orphan*/  stderr ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int system (char*) ; 
 int xdp_flags ; 

int main(int argc, char **argv)
{
	__u32 mode_flags = XDP_FLAGS_DRV_MODE | XDP_FLAGS_SKB_MODE;
	struct addrinfo *a, hints = { .ai_family = AF_INET };
	struct rlimit r = {RLIM_INFINITY, RLIM_INFINITY};
	__u16 count = XDPING_DEFAULT_COUNT;
	struct pinginfo pinginfo = { 0 };
	const char *optstr = "c:I:NsS";
	struct bpf_program *main_prog;
	int prog_fd = -1, map_fd = -1;
	struct sockaddr_in rin;
	struct bpf_object *obj;
	struct bpf_map *map;
	char *ifname = NULL;
	char filename[256];
	int opt, ret = 1;
	__u32 raddr = 0;
	int server = 0;
	char cmd[256];

	while ((opt = getopt(argc, argv, optstr)) != -1) {
		switch (opt) {
		case 'c':
			count = atoi(optarg);
			if (count < 1 || count > XDPING_MAX_COUNT) {
				fprintf(stderr,
					"min count is 1, max count is %d\n",
					XDPING_MAX_COUNT);
				return 1;
			}
			break;
		case 'I':
			ifname = optarg;
			ifindex = if_nametoindex(ifname);
			if (!ifindex) {
				fprintf(stderr, "Could not get interface %s\n",
					ifname);
				return 1;
			}
			break;
		case 'N':
			xdp_flags |= XDP_FLAGS_DRV_MODE;
			break;
		case 's':
			/* use server program */
			server = 1;
			break;
		case 'S':
			xdp_flags |= XDP_FLAGS_SKB_MODE;
			break;
		default:
			show_usage(basename(argv[0]));
			return 1;
		}
	}

	if (!ifname) {
		show_usage(basename(argv[0]));
		return 1;
	}
	if (!server && optind == argc) {
		show_usage(basename(argv[0]));
		return 1;
	}

	if ((xdp_flags & mode_flags) == mode_flags) {
		fprintf(stderr, "-N or -S can be specified, not both.\n");
		show_usage(basename(argv[0]));
		return 1;
	}

	if (!server) {
		/* Only supports IPv4; see hints initiailization above. */
		if (getaddrinfo(argv[optind], NULL, &hints, &a) || !a) {
			fprintf(stderr, "Could not resolve %s\n", argv[optind]);
			return 1;
		}
		memcpy(&rin, a->ai_addr, sizeof(rin));
		raddr = rin.sin_addr.s_addr;
		freeaddrinfo(a);
	}

	if (setrlimit(RLIMIT_MEMLOCK, &r)) {
		perror("setrlimit(RLIMIT_MEMLOCK)");
		return 1;
	}

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (bpf_prog_load(filename, BPF_PROG_TYPE_XDP, &obj, &prog_fd)) {
		fprintf(stderr, "load of %s failed\n", filename);
		return 1;
	}

	main_prog = bpf_object__find_program_by_title(obj,
						      server ? "xdpserver" :
							       "xdpclient");
	if (main_prog)
		prog_fd = bpf_program__fd(main_prog);
	if (!main_prog || prog_fd < 0) {
		fprintf(stderr, "could not find xdping program");
		return 1;
	}

	map = bpf_map__next(NULL, obj);
	if (map)
		map_fd = bpf_map__fd(map);
	if (!map || map_fd < 0) {
		fprintf(stderr, "Could not find ping map");
		goto done;
	}

	signal(SIGINT, cleanup);
	signal(SIGTERM, cleanup);

	printf("Setting up XDP for %s, please wait...\n", ifname);

	printf("XDP setup disrupts network connectivity, hit Ctrl+C to quit\n");

	if (bpf_set_link_xdp_fd(ifindex, prog_fd, xdp_flags) < 0) {
		fprintf(stderr, "Link set xdp fd failed for %s\n", ifname);
		goto done;
	}

	if (server) {
		close(prog_fd);
		close(map_fd);
		printf("Running server on %s; press Ctrl+C to exit...\n",
		       ifname);
		do { } while (1);
	}

	/* Start xdping-ing from last regular ping reply, e.g. for a count
	 * of 10 ICMP requests, we start xdping-ing using reply with seq number
	 * 10.  The reason the last "real" ping RTT is much higher is that
	 * the ping program sees the ICMP reply associated with the last
	 * XDP-generated packet, so ping doesn't get a reply until XDP is done.
	 */
	pinginfo.seq = htons(count);
	pinginfo.count = count;

	if (bpf_map_update_elem(map_fd, &raddr, &pinginfo, BPF_ANY)) {
		fprintf(stderr, "could not communicate with BPF map: %s\n",
			strerror(errno));
		cleanup(0);
		goto done;
	}

	/* We need to wait for XDP setup to complete. */
	sleep(10);

	snprintf(cmd, sizeof(cmd), "ping -c %d -I %s %s",
		 count, ifname, argv[optind]);

	printf("\nNormal ping RTT data\n");
	printf("[Ignore final RTT; it is distorted by XDP using the reply]\n");

	ret = system(cmd);

	if (!ret)
		ret = get_stats(map_fd, count, raddr);

	cleanup(0);

done:
	if (prog_fd > 0)
		close(prog_fd);
	if (map_fd > 0)
		close(map_fd);

	return ret;
}