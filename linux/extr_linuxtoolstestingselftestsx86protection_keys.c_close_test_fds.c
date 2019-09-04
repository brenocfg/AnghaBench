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
 int /*<<< orphan*/  close (int) ; 
 int nr_test_fds ; 
 int* test_fds ; 

void close_test_fds(void)
{
	int i;

	for (i = 0; i < nr_test_fds; i++) {
		if (test_fds[i] < 0)
			continue;
		close(test_fds[i]);
		test_fds[i] = -1;
	}
	nr_test_fds = 0;
}