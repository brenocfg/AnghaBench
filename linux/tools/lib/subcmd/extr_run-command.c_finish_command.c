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
struct child_process {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int wait_or_whine (int /*<<< orphan*/ ) ; 

int finish_command(struct child_process *cmd)
{
	return wait_or_whine(cmd->pid);
}