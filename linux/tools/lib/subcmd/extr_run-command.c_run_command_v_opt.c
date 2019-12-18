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
struct child_process {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  prepare_run_command_v_opt (struct child_process*,char const**,int) ; 
 int run_command (struct child_process*) ; 

int run_command_v_opt(const char **argv, int opt)
{
	struct child_process cmd;
	prepare_run_command_v_opt(&cmd, argv, opt);
	return run_command(&cmd);
}