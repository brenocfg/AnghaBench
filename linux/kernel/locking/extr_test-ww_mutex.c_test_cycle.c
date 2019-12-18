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
 int __test_cycle (unsigned int) ; 

__attribute__((used)) static int test_cycle(unsigned int ncpus)
{
	unsigned int n;
	int ret;

	for (n = 2; n <= ncpus + 1; n++) {
		ret = __test_cycle(n);
		if (ret)
			return ret;
	}

	return 0;
}