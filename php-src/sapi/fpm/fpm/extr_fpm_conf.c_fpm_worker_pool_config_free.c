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
struct key_value_s {struct key_value_s* value; struct key_value_s* key; struct key_value_s* next; } ;
struct fpm_worker_pool_config_s {struct key_value_s* env; struct key_value_s* php_admin_values; struct key_value_s* php_values; struct key_value_s* apparmor_hat; struct key_value_s* security_limit_extensions; struct key_value_s* chdir; struct key_value_s* chroot; struct key_value_s* slowlog; struct key_value_s* access_format; struct key_value_s* access_log; struct key_value_s* ping_response; struct key_value_s* ping_path; struct key_value_s* pm_status_path; struct key_value_s* listen_allowed_clients; struct key_value_s* listen_mode; struct key_value_s* listen_group; struct key_value_s* listen_owner; struct key_value_s* listen_address; struct key_value_s* group; struct key_value_s* user; struct key_value_s* prefix; struct key_value_s* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct key_value_s*) ; 

int fpm_worker_pool_config_free(struct fpm_worker_pool_config_s *wpc) /* {{{ */
{
	struct key_value_s *kv, *kv_next;

	free(wpc->name);
	free(wpc->prefix);
	free(wpc->user);
	free(wpc->group);
	free(wpc->listen_address);
	free(wpc->listen_owner);
	free(wpc->listen_group);
	free(wpc->listen_mode);
	free(wpc->listen_allowed_clients);
	free(wpc->pm_status_path);
	free(wpc->ping_path);
	free(wpc->ping_response);
	free(wpc->access_log);
	free(wpc->access_format);
	free(wpc->slowlog);
	free(wpc->chroot);
	free(wpc->chdir);
	free(wpc->security_limit_extensions);
#ifdef HAVE_APPARMOR
	free(wpc->apparmor_hat);
#endif

	for (kv = wpc->php_values; kv; kv = kv_next) {
		kv_next = kv->next;
		free(kv->key);
		free(kv->value);
		free(kv);
	}
	for (kv = wpc->php_admin_values; kv; kv = kv_next) {
		kv_next = kv->next;
		free(kv->key);
		free(kv->value);
		free(kv);
	}
	for (kv = wpc->env; kv; kv = kv_next) {
		kv_next = kv->next;
		free(kv->key);
		free(kv->value);
		free(kv);
	}

	return 0;
}