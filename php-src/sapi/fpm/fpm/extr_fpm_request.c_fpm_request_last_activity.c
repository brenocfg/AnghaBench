#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct timeval {int dummy; } ;
struct fpm_scoreboard_proc_s {struct timeval tv; } ;
struct fpm_child_s {int /*<<< orphan*/  scoreboard_i; TYPE_1__* wp; } ;
struct TYPE_2__ {int /*<<< orphan*/  scoreboard; } ;

/* Variables and functions */
 struct fpm_scoreboard_proc_s* fpm_scoreboard_proc_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int fpm_request_last_activity(struct fpm_child_s *child, struct timeval *tv) /* {{{ */
{
	struct fpm_scoreboard_proc_s *proc;

	if (!tv) return -1;

	proc = fpm_scoreboard_proc_get(child->wp->scoreboard, child->scoreboard_i);
	if (!proc) {
		return -1;
	}

	*tv = proc->tv;

	return 1;
}