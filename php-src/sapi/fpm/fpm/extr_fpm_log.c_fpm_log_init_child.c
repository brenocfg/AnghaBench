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
struct fpm_worker_pool_s {int log_fd; struct fpm_worker_pool_s* next; TYPE_1__* config; } ;
struct TYPE_2__ {scalar_t__ access_format; scalar_t__* access_log; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int) ; 
 int fpm_log_fd ; 
 int /*<<< orphan*/  fpm_log_format ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int /*<<< orphan*/  strdup (scalar_t__) ; 

int fpm_log_init_child(struct fpm_worker_pool_s *wp)  /* {{{ */
{
	if (!wp || !wp->config) {
		return -1;
	}

	if (wp->config->access_log && *wp->config->access_log) {
		if (wp->config->access_format) {
			fpm_log_format = strdup(wp->config->access_format);
		}
	}

	if (fpm_log_fd == -1) {
		fpm_log_fd = wp->log_fd;
	}


	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		if (wp->log_fd > -1 && wp->log_fd != fpm_log_fd) {
			close(wp->log_fd);
			wp->log_fd = -1;
		}
	}

	return 0;
}