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
struct fpm_worker_pool_s {struct fpm_worker_pool_s* next; } ;
struct TYPE_2__ {int max_requests; int listening_socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_CLEANUP_CHILD ; 
 int /*<<< orphan*/  FPM_PCTL_ACTION_SET ; 
 int /*<<< orphan*/  FPM_PCTL_STATE_TERMINATING ; 
 int fpm_children_create_initial (struct fpm_worker_pool_s*) ; 
 int /*<<< orphan*/  fpm_cleanups_run (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpm_event_loop (int) ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  fpm_pctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 

int fpm_run(int *max_requests) /* {{{ */
{
	struct fpm_worker_pool_s *wp;

	/* create initial children in all pools */
	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		int is_parent;

		is_parent = fpm_children_create_initial(wp);

		if (!is_parent) {
			goto run_child;
		}

		/* handle error */
		if (is_parent == 2) {
			fpm_pctl(FPM_PCTL_STATE_TERMINATING, FPM_PCTL_ACTION_SET);
			fpm_event_loop(1);
		}
	}

	/* run event loop forever */
	fpm_event_loop(0);

run_child: /* only workers reach this point */

	fpm_cleanups_run(FPM_CLEANUP_CHILD);

	*max_requests = fpm_globals.max_requests;
	return fpm_globals.listening_socket;
}