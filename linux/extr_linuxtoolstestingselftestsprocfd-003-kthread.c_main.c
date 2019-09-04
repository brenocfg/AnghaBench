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
 int kernel_thread_fd (unsigned int) ; 
 int /*<<< orphan*/  test_lookup (int) ; 
 int /*<<< orphan*/  test_readdir (int) ; 

int main(void)
{
	unsigned int pid;
	int fd;

	/*
	 * In theory this will loop indefinitely if kernel threads are exiled
	 * from /proc.
	 *
	 * Start with kthreadd.
	 */
	pid = 2;
	while ((fd = kernel_thread_fd(pid)) == -1 && pid < 1024) {
		pid++;
	}
	/* EACCES if run as non-root. */
	if (pid >= 1024)
		return 1;

	test_readdir(fd);
	test_lookup(fd);

	return 0;
}