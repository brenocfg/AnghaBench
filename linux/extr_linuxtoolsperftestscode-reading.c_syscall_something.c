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
 scalar_t__ pipe (int*) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 

__attribute__((used)) static void syscall_something(void)
{
	int pipefd[2];
	int i;

	for (i = 0; i < 1000; i++) {
		if (pipe(pipefd) < 0) {
			pr_debug("pipe failed\n");
			break;
		}
		close(pipefd[1]);
		close(pipefd[0]);
	}
}