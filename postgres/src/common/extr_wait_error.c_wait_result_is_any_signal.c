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
 int WEXITSTATUS (int) ; 
 scalar_t__ WIFEXITED (int) ; 
 scalar_t__ WIFSIGNALED (int) ; 

bool
wait_result_is_any_signal(int exit_status, bool include_command_not_found)
{
	if (WIFSIGNALED(exit_status))
		return true;
	if (WIFEXITED(exit_status) &&
		WEXITSTATUS(exit_status) > (include_command_not_found ? 125 : 128))
		return true;
	return false;
}