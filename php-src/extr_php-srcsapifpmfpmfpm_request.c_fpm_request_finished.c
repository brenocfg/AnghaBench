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
struct timeval {int dummy; } ;
struct fpm_scoreboard_proc_s {struct timeval tv; int /*<<< orphan*/  request_stage; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_REQUEST_FINISHED ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 int /*<<< orphan*/  fpm_clock_get (struct timeval*) ; 
 struct fpm_scoreboard_proc_s* fpm_scoreboard_proc_acquire (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_scoreboard_proc_release (struct fpm_scoreboard_proc_s*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*) ; 

void fpm_request_finished() /* {{{ */
{
	struct fpm_scoreboard_proc_s *proc;
	struct timeval now;

	fpm_clock_get(&now);

	proc = fpm_scoreboard_proc_acquire(NULL, -1, 0);
	if (proc == NULL) {
		zlog(ZLOG_WARNING, "failed to acquire proc scoreboard");
		return;
	}

	proc->request_stage = FPM_REQUEST_FINISHED;
	proc->tv = now;
	fpm_scoreboard_proc_release(proc);
}