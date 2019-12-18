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
typedef  unsigned int time_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_INTERVAL_S ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ bpf_map_lookup_elem (unsigned int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int /*<<< orphan*/ ) ; 
 unsigned int time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void poll_stats(unsigned int map_fd, unsigned int kill_after_s)
{
	time_t started_at = time(NULL);
	__u64 value = 0;
	int key = 0;


	while (!kill_after_s || time(NULL) - started_at <= kill_after_s) {
		sleep(STATS_INTERVAL_S);

		assert(bpf_map_lookup_elem(map_fd, &key, &value) == 0);

		printf("icmp \"packet too big\" sent: %10llu pkts\n", value);
	}
}