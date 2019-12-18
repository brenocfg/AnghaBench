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
struct fpm_worker_pool_s {scalar_t__ limit_extensions; struct fpm_worker_pool_s* home; struct fpm_worker_pool_s* user; struct fpm_worker_pool_s* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  fpm_unix_free_socket_premissions (struct fpm_worker_pool_s*) ; 
 int /*<<< orphan*/  fpm_worker_pool_free_limit_extensions (scalar_t__) ; 
 int /*<<< orphan*/  free (struct fpm_worker_pool_s*) ; 

void fpm_worker_pool_free(struct fpm_worker_pool_s *wp) /* {{{ */
{
	if (wp->config) {
		free(wp->config);
	}
	if (wp->user) {
		free(wp->user);
	}
	if (wp->home) {
		free(wp->home);
	}
	if (wp->limit_extensions) {
		fpm_worker_pool_free_limit_extensions(wp->limit_extensions);
	}
	fpm_unix_free_socket_premissions(wp);
	free(wp);
}