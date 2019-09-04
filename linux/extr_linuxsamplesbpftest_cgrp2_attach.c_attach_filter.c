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
typedef  int /*<<< orphan*/  key ;
typedef  int /*<<< orphan*/  byte_cnt ;

/* Variables and functions */
 int /*<<< orphan*/  BPF_MAP_TYPE_ARRAY ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int MAP_KEY_BYTES ; 
 int MAP_KEY_PACKETS ; 
 int /*<<< orphan*/  assert (int) ; 
 int bpf_create_map (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 
 char* bpf_log_buf ; 
 scalar_t__ bpf_map_lookup_elem (int,int*,long long*) ; 
 int bpf_prog_attach (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int prog_load (int,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 char* strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int attach_filter(int cg_fd, int type, int verdict)
{
	int prog_fd, map_fd, ret, key;
	long long pkt_cnt, byte_cnt;

	map_fd = bpf_create_map(BPF_MAP_TYPE_ARRAY,
				sizeof(key), sizeof(byte_cnt),
				256, 0);
	if (map_fd < 0) {
		printf("Failed to create map: '%s'\n", strerror(errno));
		return EXIT_FAILURE;
	}

	prog_fd = prog_load(map_fd, verdict);
	printf("Output from kernel verifier:\n%s\n-------\n", bpf_log_buf);

	if (prog_fd < 0) {
		printf("Failed to load prog: '%s'\n", strerror(errno));
		return EXIT_FAILURE;
	}

	ret = bpf_prog_attach(prog_fd, cg_fd, type, 0);
	if (ret < 0) {
		printf("Failed to attach prog to cgroup: '%s'\n",
		       strerror(errno));
		return EXIT_FAILURE;
	}
	while (1) {
		key = MAP_KEY_PACKETS;
		assert(bpf_map_lookup_elem(map_fd, &key, &pkt_cnt) == 0);

		key = MAP_KEY_BYTES;
		assert(bpf_map_lookup_elem(map_fd, &key, &byte_cnt) == 0);

		printf("cgroup received %lld packets, %lld bytes\n",
		       pkt_cnt, byte_cnt);
		sleep(1);
	}

	return EXIT_SUCCESS;
}