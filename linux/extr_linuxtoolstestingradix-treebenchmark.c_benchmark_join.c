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

/* Variables and functions */
 scalar_t__ __benchmark_join (int,int,int) ; 
 int /*<<< orphan*/  printv (int,char*,int,unsigned long,long long) ; 

__attribute__((used)) static void benchmark_join(unsigned long step)
{
	int i, j, idx;
	long long nsec = 0;

	for (idx = 0; idx < 1 << 10; idx += step) {
		for (i = 1; i < 15; i++) {
			for (j = 0; j < i; j++) {
				nsec += __benchmark_join(idx, i, j);
			}
		}
	}

	printv(2, "Size %8d, step %8ld, join time %10lld ns\n",
			1 << 10, step, nsec);
}