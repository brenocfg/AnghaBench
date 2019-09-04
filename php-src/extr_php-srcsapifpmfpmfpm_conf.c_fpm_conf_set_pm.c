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
typedef  int /*<<< orphan*/  zval ;
struct fpm_worker_pool_config_s {int /*<<< orphan*/  pm; } ;

/* Variables and functions */
 int /*<<< orphan*/  PM_STYLE_DYNAMIC ; 
 int /*<<< orphan*/  PM_STYLE_ONDEMAND ; 
 int /*<<< orphan*/  PM_STYLE_STATIC ; 
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 

__attribute__((used)) static char *fpm_conf_set_pm(zval *value, void **config, intptr_t offset) /* {{{ */
{
	char *val = Z_STRVAL_P(value);
	struct fpm_worker_pool_config_s  *c = *config;
	if (!strcasecmp(val, "static")) {
		c->pm = PM_STYLE_STATIC;
	} else if (!strcasecmp(val, "dynamic")) {
		c->pm = PM_STYLE_DYNAMIC;
	} else if (!strcasecmp(val, "ondemand")) {
		c->pm = PM_STYLE_ONDEMAND;
	} else {
		return "invalid process manager (static, dynamic or ondemand)";
	}
	return NULL;
}