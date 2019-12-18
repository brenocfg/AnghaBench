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
struct fpm_worker_pool_s {int /*<<< orphan*/  scoreboard; int /*<<< orphan*/  children; int /*<<< orphan*/  config; struct fpm_worker_pool_s* next; } ;
struct TYPE_2__ {scalar_t__ parent_pid; } ;

/* Variables and functions */
 int FPM_CLEANUP_CHILD ; 
 int /*<<< orphan*/  fpm_children_free (int /*<<< orphan*/ ) ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  fpm_scoreboard_free (int /*<<< orphan*/ ) ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int /*<<< orphan*/  fpm_worker_pool_config_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_worker_pool_free (struct fpm_worker_pool_s*) ; 
 scalar_t__ getpid () ; 

__attribute__((used)) static void fpm_worker_pool_cleanup(int which, void *arg) /* {{{ */
{
	struct fpm_worker_pool_s *wp, *wp_next;

	for (wp = fpm_worker_all_pools; wp; wp = wp_next) {
		wp_next = wp->next;
		fpm_worker_pool_config_free(wp->config);
		fpm_children_free(wp->children);
		if ((which & FPM_CLEANUP_CHILD) == 0 && fpm_globals.parent_pid == getpid()) {
			fpm_scoreboard_free(wp->scoreboard);
		}
		fpm_worker_pool_free(wp);
	}
	fpm_worker_all_pools = NULL;
}