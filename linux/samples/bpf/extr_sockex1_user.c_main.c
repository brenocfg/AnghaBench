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
struct bpf_object {int dummy; } ;
typedef  int /*<<< orphan*/  prog_fd ;
typedef  int /*<<< orphan*/  filename ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_PROG_TYPE_SOCKET_FILTER ; 
 int IPPROTO_ICMP ; 
 int IPPROTO_TCP ; 
 int IPPROTO_UDP ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_ATTACH_BPF ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bpf_map_lookup_elem (int,int*,long long*) ; 
 int bpf_object__find_map_fd_by_name (struct bpf_object*,char*) ; 
 scalar_t__ bpf_prog_load (char*,int /*<<< orphan*/ ,struct bpf_object**,int*) ; 
 int open_raw_sock (char*) ; 
 int /*<<< orphan*/ * popen (char*,char*) ; 
 int /*<<< orphan*/  printf (char*,long long,long long,long long) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int main(int ac, char **argv)
{
	struct bpf_object *obj;
	int map_fd, prog_fd;
	char filename[256];
	int i, sock;
	FILE *f;

	snprintf(filename, sizeof(filename), "%s_kern.o", argv[0]);

	if (bpf_prog_load(filename, BPF_PROG_TYPE_SOCKET_FILTER,
			  &obj, &prog_fd))
		return 1;

	map_fd = bpf_object__find_map_fd_by_name(obj, "my_map");

	sock = open_raw_sock("lo");

	assert(setsockopt(sock, SOL_SOCKET, SO_ATTACH_BPF, &prog_fd,
			  sizeof(prog_fd)) == 0);

	f = popen("ping -4 -c5 localhost", "r");
	(void) f;

	for (i = 0; i < 5; i++) {
		long long tcp_cnt, udp_cnt, icmp_cnt;
		int key;

		key = IPPROTO_TCP;
		assert(bpf_map_lookup_elem(map_fd, &key, &tcp_cnt) == 0);

		key = IPPROTO_UDP;
		assert(bpf_map_lookup_elem(map_fd, &key, &udp_cnt) == 0);

		key = IPPROTO_ICMP;
		assert(bpf_map_lookup_elem(map_fd, &key, &icmp_cnt) == 0);

		printf("TCP %lld UDP %lld ICMP %lld bytes\n",
		       tcp_cnt, udp_cnt, icmp_cnt);
		sleep(1);
	}

	return 0;
}