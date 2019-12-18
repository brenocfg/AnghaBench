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
struct fpm_worker_pool_s {TYPE_1__* config; int /*<<< orphan*/  listening_socket; } ;
struct TYPE_4__ {int /*<<< orphan*/  listening_socket; int /*<<< orphan*/  max_requests; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; int /*<<< orphan*/  pm_max_requests; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPM_EXIT_SOFTWARE ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int /*<<< orphan*/  dup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fpm_env_init_child (struct fpm_worker_pool_s*) ; 
 TYPE_2__ fpm_globals ; 
 scalar_t__ fpm_log_init_child (struct fpm_worker_pool_s*) ; 
 scalar_t__ fpm_php_init_child (struct fpm_worker_pool_s*) ; 
 scalar_t__ fpm_signals_init_child () ; 
 scalar_t__ fpm_status_init_child (struct fpm_worker_pool_s*) ; 
 scalar_t__ fpm_stdio_init_child (struct fpm_worker_pool_s*) ; 
 scalar_t__ fpm_unix_init_child (struct fpm_worker_pool_s*) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fpm_child_init(struct fpm_worker_pool_s *wp) /* {{{ */
{
	fpm_globals.max_requests = wp->config->pm_max_requests;
	fpm_globals.listening_socket = dup(wp->listening_socket);

	if (0 > fpm_stdio_init_child(wp)  ||
	    0 > fpm_log_init_child(wp)    ||
	    0 > fpm_status_init_child(wp) ||
	    0 > fpm_unix_init_child(wp)   ||
	    0 > fpm_signals_init_child()  ||
	    0 > fpm_env_init_child(wp)    ||
	    0 > fpm_php_init_child(wp)) {

		zlog(ZLOG_ERROR, "[pool %s] child failed to initialize", wp->config->name);
		exit(FPM_EXIT_SOFTWARE);
	}
}