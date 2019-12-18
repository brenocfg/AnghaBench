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
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 scalar_t__ child_pid ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  ksft_exit_pass () ; 
 int /*<<< orphan*/  ksft_print_header () ; 
 int /*<<< orphan*/  launch_tests () ; 
 int /*<<< orphan*/  trigger_tests () ; 
 int /*<<< orphan*/  wait (int /*<<< orphan*/ *) ; 

int main(int argc, char **argv)
{
	pid_t pid;
	int ret;

	ksft_print_header();

	pid = fork();
	if (!pid) {
		trigger_tests();
		exit(0);
	}

	child_pid = pid;

	wait(NULL);

	launch_tests();

	wait(NULL);

	ksft_exit_pass();
}