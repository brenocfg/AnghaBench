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
struct TYPE_4__ {scalar_t__ syslog_ident; int /*<<< orphan*/  log_limit; scalar_t__ error_log; scalar_t__ pid_file; scalar_t__ events_mechanism; } ;
struct TYPE_3__ {scalar_t__ config; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZLOG_DEFAULT_LIMIT ; 
 TYPE_2__ fpm_global_config ; 
 TYPE_1__ fpm_globals ; 
 int /*<<< orphan*/  free (scalar_t__) ; 

__attribute__((used)) static void fpm_conf_cleanup(int which, void *arg) /* {{{ */
{
	free(fpm_global_config.pid_file);
	free(fpm_global_config.error_log);
	free(fpm_global_config.events_mechanism);
	fpm_global_config.pid_file = 0;
	fpm_global_config.error_log = 0;
	fpm_global_config.log_limit = ZLOG_DEFAULT_LIMIT;
#ifdef HAVE_SYSLOG_H
	free(fpm_global_config.syslog_ident);
	fpm_global_config.syslog_ident = 0;
#endif
	free(fpm_globals.config);
}