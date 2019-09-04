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
typedef  int __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  __NR_geteuid ; 
 int max_cnt ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ) ; 
 int time_get_ns () ; 

__attribute__((used)) static void test_percpu_hash_prealloc(int cpu)
{
	__u64 start_time;
	int i;

	start_time = time_get_ns();
	for (i = 0; i < max_cnt; i++)
		syscall(__NR_geteuid);
	printf("%d:percpu_hash_map_perf pre-alloc %lld events per sec\n",
	       cpu, max_cnt * 1000000000ll / (time_get_ns() - start_time));
}