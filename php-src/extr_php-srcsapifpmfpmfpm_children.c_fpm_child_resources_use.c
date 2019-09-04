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
struct fpm_worker_pool_s {int /*<<< orphan*/  scoreboard; struct fpm_worker_pool_s* next; } ;
struct fpm_child_s {int /*<<< orphan*/  scoreboard_i; struct fpm_worker_pool_s* wp; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpm_child_free (struct fpm_child_s*) ; 
 int /*<<< orphan*/  fpm_scoreboard_child_use (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_scoreboard_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_stdio_child_use_pipes (struct fpm_child_s*) ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int /*<<< orphan*/  getpid () ; 

__attribute__((used)) static void fpm_child_resources_use(struct fpm_child_s *child) /* {{{ */
{
	struct fpm_worker_pool_s *wp;
	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		if (wp == child->wp) {
			continue;
		}
		fpm_scoreboard_free(wp->scoreboard);
	}

	fpm_scoreboard_child_use(child->wp->scoreboard, child->scoreboard_i, getpid());
	fpm_stdio_child_use_pipes(child);
	fpm_child_free(child);
}