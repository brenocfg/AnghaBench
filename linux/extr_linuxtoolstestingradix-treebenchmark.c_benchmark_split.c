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
 scalar_t__ __benchmark_split (int,int,int) ; 
 int /*<<< orphan*/  printv (int,char*,unsigned long,unsigned long,long long) ; 

__attribute__((used)) static void benchmark_split(unsigned long size, unsigned long step)
{
	int i, j, idx;
	long long nsec = 0;


	for (idx = 0; idx < size; idx += step) {
		for (i = 3; i < 11; i++) {
			for (j = 0; j < i; j++) {
				nsec += __benchmark_split(idx, i, j);
			}
		}
	}

	printv(2, "Size %8ld, step %8ld, split time %10lld ns\n",
			size, step, nsec);

}