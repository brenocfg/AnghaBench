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
typedef  int uint32_t ;
struct stats {int uid; int /*<<< orphan*/  bytes; int /*<<< orphan*/  packets; } ;

/* Variables and functions */
 int UINT32_MAX ; 
 int bpf_map_get_next_key (int /*<<< orphan*/ ,int*,int*) ; 
 int bpf_map_lookup_elem (int /*<<< orphan*/ ,int*,struct stats*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  error (int,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  map_fd ; 
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_table(void)
{
	struct stats curEntry;
	uint32_t curN = UINT32_MAX;
	uint32_t nextN;
	int res;

	while (bpf_map_get_next_key(map_fd, &curN, &nextN) > -1) {
		curN = nextN;
		res = bpf_map_lookup_elem(map_fd, &curN, &curEntry);
		if (res < 0) {
			error(1, errno, "fail to get entry value of Key: %u\n",
				curN);
		} else {
			printf("cookie: %u, uid: 0x%x, Packet Count: %lu,"
				" Bytes Count: %lu\n", curN, curEntry.uid,
				curEntry.packets, curEntry.bytes);
		}
	}
}