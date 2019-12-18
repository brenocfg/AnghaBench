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
 int /*<<< orphan*/  __do_binderfs_test () ; 
 scalar_t__ geteuid () ; 
 int /*<<< orphan*/  ksft_print_msg (char*) ; 

__attribute__((used)) static void binderfs_test_privileged()
{
	if (geteuid() != 0)
		ksft_print_msg(
			"Tests are not run as root. Skipping privileged tests\n");
	else
		__do_binderfs_test();
}