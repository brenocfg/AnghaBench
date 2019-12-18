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
struct key_value_s {int /*<<< orphan*/  key; struct key_value_s* next; } ;
struct fpm_worker_pool_s {TYPE_1__* config; } ;
struct TYPE_2__ {struct key_value_s* php_admin_values; struct key_value_s* php_values; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_INI_SYSTEM ; 
 int /*<<< orphan*/  ZEND_INI_USER ; 
 int /*<<< orphan*/  ZLOG_ERROR ; 
 int fpm_php_apply_defines_ex (struct key_value_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zlog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fpm_php_apply_defines(struct fpm_worker_pool_s *wp) /* {{{ */
{
	struct key_value_s *kv;

	for (kv = wp->config->php_values; kv; kv = kv->next) {
		if (fpm_php_apply_defines_ex(kv, ZEND_INI_USER) == -1) {
			zlog(ZLOG_ERROR, "Unable to set php_value '%s'", kv->key);
		}
	}

	for (kv = wp->config->php_admin_values; kv; kv = kv->next) {
		if (fpm_php_apply_defines_ex(kv, ZEND_INI_SYSTEM) == -1) {
			zlog(ZLOG_ERROR, "Unable to set php_admin_value '%s'", kv->key);
		}
	}

	return 0;
}