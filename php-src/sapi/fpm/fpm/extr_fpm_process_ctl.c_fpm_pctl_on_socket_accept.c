#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct fpm_worker_pool_s {scalar_t__ running_children; int warn_max_children; TYPE_1__* config; struct fpm_child_s* children; int /*<<< orphan*/  scoreboard; scalar_t__ socket_event_set; } ;
struct fpm_event_s {int dummy; } ;
struct fpm_child_s {struct fpm_child_s* next; } ;
struct TYPE_4__ {scalar_t__ parent_pid; scalar_t__ is_child; } ;
struct TYPE_3__ {scalar_t__ pm_max_children; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_SCOREBOARD_ACTION_INC ; 
 int /*<<< orphan*/  ZLOG_DEBUG ; 
 int /*<<< orphan*/  ZLOG_WARNING ; 
 int /*<<< orphan*/  fpm_children_make (struct fpm_worker_pool_s*,int,int,int) ; 
 TYPE_2__ fpm_globals ; 
 scalar_t__ fpm_request_is_idle (struct fpm_child_s*) ; 
 int /*<<< orphan*/  fpm_scoreboard_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

void fpm_pctl_on_socket_accept(struct fpm_event_s *ev, short which, void *arg) /* {{{ */
{
	struct fpm_worker_pool_s *wp = (struct fpm_worker_pool_s *)arg;
	struct fpm_child_s *child;


	if (fpm_globals.parent_pid != getpid()) {
		/* prevent a event race condition when child process
		 * have not set up its own event loop */
		return;
	}

	wp->socket_event_set = 0;

/*	zlog(ZLOG_DEBUG, "[pool %s] heartbeat running_children=%d", wp->config->name, wp->running_children);*/

	if (wp->running_children >= wp->config->pm_max_children) {
		if (!wp->warn_max_children) {
			fpm_scoreboard_update(0, 0, 0, 0, 0, 1, 0, FPM_SCOREBOARD_ACTION_INC, wp->scoreboard);
			zlog(ZLOG_WARNING, "[pool %s] server reached max_children setting (%d), consider raising it", wp->config->name, wp->config->pm_max_children);
			wp->warn_max_children = 1;
		}

		return;
	}

	for (child = wp->children; child; child = child->next) {
		/* if there is at least on idle child, it will handle the connection, stop here */
		if (fpm_request_is_idle(child)) {
			return;
		}
	}

	wp->warn_max_children = 0;
	fpm_children_make(wp, 1, 1, 1);

	if (fpm_globals.is_child) {
		return;
	}

	zlog(ZLOG_DEBUG, "[pool %s] got accept without idle child available .... I forked", wp->config->name);
}