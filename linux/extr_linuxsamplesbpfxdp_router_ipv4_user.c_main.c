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
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ XDP_FLAGS_SKB_MODE ; 
 char* bpf_log_buf ; 
 scalar_t__ bpf_set_link_xdp_fd (int,int,scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ flags ; 
 int /*<<< orphan*/  get_arp_table (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_route_table (int /*<<< orphan*/ ) ; 
 int if_nametoindex (char*) ; 
 int* ifindex_list ; 
 int /*<<< orphan*/  int_exit ; 
 scalar_t__ load_bpf_file (char*) ; 
 scalar_t__ malloc (int) ; 
 scalar_t__ monitor_route () ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int* prog_fd ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int total_ifindex ; 

int main(int ac, char **argv)
{
	char filename[256];
	char **ifname_list;
	int i = 1;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);
	if (ac < 2) {
		printf("usage: %s [-S] Interface name list\n", argv[0]);
		return 1;
	}
	if (!strcmp(argv[1], "-S")) {
		flags = XDP_FLAGS_SKB_MODE;
		total_ifindex = ac - 2;
		ifname_list = (argv + 2);
	} else {
		flags = 0;
		total_ifindex = ac - 1;
		ifname_list = (argv + 1);
	}
	if (load_bpf_file(filename)) {
		printf("%s", bpf_log_buf);
		return 1;
	}
	printf("\n**************loading bpf file*********************\n\n\n");
	if (!prog_fd[0]) {
		printf("load_bpf_file: %s\n", strerror(errno));
		return 1;
	}
	ifindex_list = (int *)malloc(total_ifindex * sizeof(int *));
	for (i = 0; i < total_ifindex; i++) {
		ifindex_list[i] = if_nametoindex(ifname_list[i]);
		if (!ifindex_list[i]) {
			printf("Couldn't translate interface name: %s",
			       strerror(errno));
			return 1;
		}
	}
	for (i = 0; i < total_ifindex; i++) {
		if (bpf_set_link_xdp_fd(ifindex_list[i], prog_fd[0], flags) < 0) {
			printf("link set xdp fd failed\n");
			int recovery_index = i;

			for (i = 0; i < recovery_index; i++)
				bpf_set_link_xdp_fd(ifindex_list[i], -1, flags);

			return 1;
		}
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