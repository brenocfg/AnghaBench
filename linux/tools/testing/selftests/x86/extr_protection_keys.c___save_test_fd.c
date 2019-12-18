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
 size_t ARRAY_SIZE (int*) ; 
 size_t nr_test_fds ; 
 int /*<<< orphan*/  pkey_assert (int) ; 
 int* test_fds ; 

void __save_test_fd(int fd)
{
	pkey_assert(fd >= 0);
	pkey_assert(nr_test_fds < ARRAY_SIZE(test_fds));
	test_fds[nr_test_fds] = fd;
	nr_test_fds++;
}