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
struct fpm_worker_pool_s {int /*<<< orphan*/ * limit_extensions; } ;

/* Variables and functions */
 scalar_t__ fpm_php_apply_defines (struct fpm_worker_pool_s*) ; 
 scalar_t__ fpm_php_set_allowed_clients (struct fpm_worker_pool_s*) ; 
 int /*<<< orphan*/ * limit_extensions ; 

int fpm_php_init_child(struct fpm_worker_pool_s *wp) /* {{{ */
{
	if (0 > fpm_php_apply_defines(wp) ||
		0 > fpm_php_set_allowed_clients(wp)) {
		return -1;
	}

	if (wp->limit_extensions) {
		/* Take ownership of limit_extensions. */
		limit_extensions = wp->limit_extensions;
		wp->limit_extensions = NULL;
	}
	return 0;
}