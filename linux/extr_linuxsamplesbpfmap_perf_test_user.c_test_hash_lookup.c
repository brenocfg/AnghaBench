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
 int /*<<< orphan*/  __NR_getpgid ; 
 int max_cnt ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  syscall (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int time_get_ns () ; 

__attribute__((used)) static void test_hash_lookup(int cpu)
{
	__u64 start_time;
	int i;

	start_time = time_get_ns();
	for (i = 0; i < max_cnt; i++)
		syscall(__NR_getpgid, 0);
	printf("%d:hash_lookup %lld lookups per sec\n",
	       cpu, max_cnt * 1000000000ll * 64 / (time_get_ns() - start_time));
}