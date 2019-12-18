#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct key_value_s {int /*<<< orphan*/  value; int /*<<< orphan*/  key; struct key_value_s* next; } ;
struct fpm_worker_pool_s {TYPE_1__* config; struct fpm_worker_pool_s* next; } ;
struct TYPE_6__ {int process_priority; int systemd_interval; int /*<<< orphan*/  rlimit_core; int /*<<< orphan*/  rlimit_files; int /*<<< orphan*/  daemonize; int /*<<< orphan*/  process_max; int /*<<< orphan*/  process_control_timeout; int /*<<< orphan*/  emergency_restart_threshold; int /*<<< orphan*/  emergency_restart_interval; int /*<<< orphan*/  log_limit; int /*<<< orphan*/  log_buffering; int /*<<< orphan*/  syslog_facility; int /*<<< orphan*/  syslog_ident; int /*<<< orphan*/  error_log; int /*<<< orphan*/  pid_file; } ;
struct TYPE_5__ {int /*<<< orphan*/  log_level; } ;
struct TYPE_4__ {int process_priority; struct key_value_s* php_admin_values; struct key_value_s* php_values; struct key_value_s* env; int /*<<< orphan*/  security_limit_extensions; int /*<<< orphan*/  clear_env; int /*<<< orphan*/  decorate_workers_output; int /*<<< orphan*/  catch_workers_output; int /*<<< orphan*/  chdir; int /*<<< orphan*/  chroot; int /*<<< orphan*/  rlimit_core; int /*<<< orphan*/  rlimit_files; int /*<<< orphan*/  request_terminate_timeout_track_finished; int /*<<< orphan*/  request_terminate_timeout; int /*<<< orphan*/  request_slowlog_trace_depth; int /*<<< orphan*/  request_slowlog_timeout; int /*<<< orphan*/  slowlog; int /*<<< orphan*/  access_format; int /*<<< orphan*/  access_log; int /*<<< orphan*/  ping_response; int /*<<< orphan*/  ping_path; int /*<<< orphan*/  pm_status_path; int /*<<< orphan*/  pm_max_requests; int /*<<< orphan*/  pm_process_idle_timeout; int /*<<< orphan*/  pm_max_spare_servers; int /*<<< orphan*/  pm_min_spare_servers; int /*<<< orphan*/  pm_start_servers; int /*<<< orphan*/  pm_max_children; int /*<<< orphan*/  pm; int /*<<< orphan*/  process_dumpable; int /*<<< orphan*/  listen_allowed_clients; int /*<<< orphan*/  listen_mode; int /*<<< orphan*/  listen_group; int /*<<< orphan*/  listen_owner; int /*<<< orphan*/  listen_acl_groups; int /*<<< orphan*/  listen_acl_users; int /*<<< orphan*/  listen_backlog; int /*<<< orphan*/  listen_address; int /*<<< orphan*/  group; int /*<<< orphan*/  user; int /*<<< orphan*/  prefix; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOL2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PM2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  STR2STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZLOG_NOTICE ; 
 int /*<<< orphan*/  fpm_event_machanism_name () ; 
 TYPE_3__ fpm_global_config ; 
 TYPE_2__ fpm_globals ; 
 struct fpm_worker_pool_s* fpm_worker_all_pools ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  zlog_get_level_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fpm_conf_dump() /* {{{ */
{
	struct fpm_worker_pool_s *wp;

	/*
	 * Please keep the same order as in fpm_conf.h and in php-fpm.conf.in
	 */
	zlog(ZLOG_NOTICE, "[global]");
	zlog(ZLOG_NOTICE, "\tpid = %s",                         STR2STR(fpm_global_config.pid_file));
	zlog(ZLOG_NOTICE, "\terror_log = %s",                   STR2STR(fpm_global_config.error_log));
#ifdef HAVE_SYSLOG_H
	zlog(ZLOG_NOTICE, "\tsyslog.ident = %s",                STR2STR(fpm_global_config.syslog_ident));
	zlog(ZLOG_NOTICE, "\tsyslog.facility = %d",             fpm_global_config.syslog_facility); /* FIXME: convert to string */
#endif
	zlog(ZLOG_NOTICE, "\tlog_buffering = %s",               BOOL2STR(fpm_global_config.log_buffering));
	zlog(ZLOG_NOTICE, "\tlog_level = %s",                   zlog_get_level_name(fpm_globals.log_level));
	zlog(ZLOG_NOTICE, "\tlog_limit = %d",                   fpm_global_config.log_limit);
	zlog(ZLOG_NOTICE, "\temergency_restart_interval = %ds", fpm_global_config.emergency_restart_interval);
	zlog(ZLOG_NOTICE, "\temergency_restart_threshold = %d", fpm_global_config.emergency_restart_threshold);
	zlog(ZLOG_NOTICE, "\tprocess_control_timeout = %ds",    fpm_global_config.process_control_timeout);
	zlog(ZLOG_NOTICE, "\tprocess.max = %d",                 fpm_global_config.process_max);
	if (fpm_global_config.process_priority == 64) {
		zlog(ZLOG_NOTICE, "\tprocess.priority = undefined");
	} else {
		zlog(ZLOG_NOTICE, "\tprocess.priority = %d", fpm_global_config.process_priority);
	}
	zlog(ZLOG_NOTICE, "\tdaemonize = %s",                   BOOL2STR(fpm_global_config.daemonize));
	zlog(ZLOG_NOTICE, "\trlimit_files = %d",                fpm_global_config.rlimit_files);
	zlog(ZLOG_NOTICE, "\trlimit_core = %d",                 fpm_global_config.rlimit_core);
	zlog(ZLOG_NOTICE, "\tevents.mechanism = %s",            fpm_event_machanism_name());
#ifdef HAVE_SYSTEMD
	zlog(ZLOG_NOTICE, "\tsystemd_interval = %ds",           fpm_global_config.systemd_interval/1000);
#endif
	zlog(ZLOG_NOTICE, " ");

	for (wp = fpm_worker_all_pools; wp; wp = wp->next) {
		struct key_value_s *kv;
		if (!wp->config) continue;
		zlog(ZLOG_NOTICE, "[%s]",                              STR2STR(wp->config->name));
		zlog(ZLOG_NOTICE, "\tprefix = %s",                     STR2STR(wp->config->prefix));
		zlog(ZLOG_NOTICE, "\tuser = %s",                       STR2STR(wp->config->user));
		zlog(ZLOG_NOTICE, "\tgroup = %s",                      STR2STR(wp->config->group));
		zlog(ZLOG_NOTICE, "\tlisten = %s",                     STR2STR(wp->config->listen_address));
		zlog(ZLOG_NOTICE, "\tlisten.backlog = %d",             wp->config->listen_backlog);
#ifdef HAVE_FPM_ACL
		zlog(ZLOG_NOTICE, "\tlisten.acl_users = %s",           STR2STR(wp->config->listen_acl_users));
		zlog(ZLOG_NOTICE, "\tlisten.acl_groups = %s",          STR2STR(wp->config->listen_acl_groups));
#endif
		zlog(ZLOG_NOTICE, "\tlisten.owner = %s",               STR2STR(wp->config->listen_owner));
		zlog(ZLOG_NOTICE, "\tlisten.group = %s",               STR2STR(wp->config->listen_group));
		zlog(ZLOG_NOTICE, "\tlisten.mode = %s",                STR2STR(wp->config->listen_mode));
		zlog(ZLOG_NOTICE, "\tlisten.allowed_clients = %s",     STR2STR(wp->config->listen_allowed_clients));
		if (wp->config->process_priority == 64) {
			zlog(ZLOG_NOTICE, "\tprocess.priority = undefined");
		} else {
			zlog(ZLOG_NOTICE, "\tprocess.priority = %d", wp->config->process_priority);
		}
		zlog(ZLOG_NOTICE, "\tprocess.dumpable = %s",           BOOL2STR(wp->config->process_dumpable));
		zlog(ZLOG_NOTICE, "\tpm = %s",                         PM2STR(wp->config->pm));
		zlog(ZLOG_NOTICE, "\tpm.max_children = %d",            wp->config->pm_max_children);
		zlog(ZLOG_NOTICE, "\tpm.start_servers = %d",           wp->config->pm_start_servers);
		zlog(ZLOG_NOTICE, "\tpm.min_spare_servers = %d",       wp->config->pm_min_spare_servers);
		zlog(ZLOG_NOTICE, "\tpm.max_spare_servers = %d",       wp->config->pm_max_spare_servers);
		zlog(ZLOG_NOTICE, "\tpm.process_idle_timeout = %d",    wp->config->pm_process_idle_timeout);
		zlog(ZLOG_NOTICE, "\tpm.max_requests = %d",            wp->config->pm_max_requests);
		zlog(ZLOG_NOTICE, "\tpm.status_path = %s",             STR2STR(wp->config->pm_status_path));
		zlog(ZLOG_NOTICE, "\tping.path = %s",                  STR2STR(wp->config->ping_path));
		zlog(ZLOG_NOTICE, "\tping.response = %s",              STR2STR(wp->config->ping_response));
		zlog(ZLOG_NOTICE, "\taccess.log = %s",                 STR2STR(wp->config->access_log));
		zlog(ZLOG_NOTICE, "\taccess.format = %s",              STR2STR(wp->config->access_format));
		zlog(ZLOG_NOTICE, "\tslowlog = %s",                    STR2STR(wp->config->slowlog));
		zlog(ZLOG_NOTICE, "\trequest_slowlog_timeout = %ds",   wp->config->request_slowlog_timeout);
		zlog(ZLOG_NOTICE, "\trequest_slowlog_trace_depth = %d", wp->config->request_slowlog_trace_depth);
		zlog(ZLOG_NOTICE, "\trequest_terminate_timeout = %ds", wp->config->request_terminate_timeout);
		zlog(ZLOG_NOTICE, "\trequest_terminate_timeout_track_finished = %s", BOOL2STR(wp->config->request_terminate_timeout_track_finished));
		zlog(ZLOG_NOTICE, "\trlimit_files = %d",               wp->config->rlimit_files);
		zlog(ZLOG_NOTICE, "\trlimit_core = %d",                wp->config->rlimit_core);
		zlog(ZLOG_NOTICE, "\tchroot = %s",                     STR2STR(wp->config->chroot));
		zlog(ZLOG_NOTICE, "\tchdir = %s",                      STR2STR(wp->config->chdir));
		zlog(ZLOG_NOTICE, "\tcatch_workers_output = %s",       BOOL2STR(wp->config->catch_workers_output));
		zlog(ZLOG_NOTICE, "\tdecorate_workers_output = %s",    BOOL2STR(wp->config->decorate_workers_output));
		zlog(ZLOG_NOTICE, "\tclear_env = %s",                  BOOL2STR(wp->config->clear_env));
		zlog(ZLOG_NOTICE, "\tsecurity.limit_extensions = %s",  wp->config->security_limit_extensions);

		for (kv = wp->config->env; kv; kv = kv->next) {
			zlog(ZLOG_NOTICE, "\tenv[%s] = %s", kv->key, kv->value);
		}

		for (kv = wp->config->php_values; kv; kv = kv->next) {
			zlog(ZLOG_NOTICE, "\tphp_value[%s] = %s", kv->key, kv->value);
		}

		for (kv = wp->config->php_admin_values; kv; kv = kv->next) {
			zlog(ZLOG_NOTICE, "\tphp_admin_value[%s] = %s", kv->key, kv->value);
		}
		zlog(ZLOG_NOTICE, " ");
	}
}