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
struct fpm_worker_pool_s {struct fpm_child_s* children; TYPE_1__* config; struct fpm_worker_pool_s* next; } ;
struct fpm_child_s {struct fpm_child_s* next; } ;
struct TYPE_2__ {int request_terminate_timeout_track_finished; int request_terminate_timeout; int request_slowlog_timeout; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpm_request_check_timed_out (struct fpm_child_s*,struct timeval*,int,int,int) ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 

__attribute__((used)) static void fpm_pctl_check_request_timeout(struct timeval *now) /* {{{ */
{
	struct fpm_worker_pool_s *wp;

	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		int track_finished = wp->config->request_terminate_timeout_track_finished;
		int terminate_timeout = wp->config->request_terminate_timeout;
		int slowlog_timeout = wp->config->request_slowlog_timeout;
		struct fpm_child_s *child;

		if (terminate_timeout || slowlog_timeout) {
			for (child = wp->children; child; child = child->next) {
				fpm_request_check_timed_out(child, now, terminate_timeout, slowlog_timeout, track_finished);
			}
		}
	}
}