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
 int /*<<< orphan*/  ksft_exit_fail_msg (char*,int) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static bool bool_arg(char **argv, int i)
{
	if (!strcmp(argv[i], "0"))
		return false;
	else if (!strcmp(argv[i], "1"))
		return true;
	else {
		ksft_exit_fail_msg("wrong argv[%d]\n", i);
		return false;
	}
}