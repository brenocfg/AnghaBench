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
struct fpm_scoreboard_s {int dummy; } ;
struct fpm_scoreboard_proc_s {int /*<<< orphan*/  start_epoch; int /*<<< orphan*/  pid; } ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 struct fpm_scoreboard_s* fpm_scoreboard ; 
 int fpm_scoreboard_i ; 
 struct fpm_scoreboard_proc_s* fpm_scoreboard_proc_get (struct fpm_scoreboard_s*,int) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void fpm_scoreboard_child_use(struct fpm_scoreboard_s *scoreboard, int child_index, pid_t pid) /* {{{ */
{
	struct fpm_scoreboard_proc_s *proc;
	fpm_scoreboard = scoreboard;
	fpm_scoreboard_i = child_index;
	proc = fpm_scoreboard_proc_get(scoreboard, child_index);
	if (!proc) {
		return;
	}
	proc->pid = pid;
	proc->start_epoch = time(NULL);
}