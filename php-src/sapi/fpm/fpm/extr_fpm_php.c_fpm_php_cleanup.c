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

/* Variables and functions */
 int /*<<< orphan*/  fpm_worker_pool_free_limit_extensions (scalar_t__) ; 
 scalar_t__ limit_extensions ; 
 int /*<<< orphan*/  php_module_shutdown () ; 
 int /*<<< orphan*/  sapi_shutdown () ; 

__attribute__((used)) static void fpm_php_cleanup(int which, void *arg) /* {{{ */
{
	php_module_shutdown();
	sapi_shutdown();
	if (limit_extensions) {
		fpm_worker_pool_free_limit_extensions(limit_extensions);
	}
}