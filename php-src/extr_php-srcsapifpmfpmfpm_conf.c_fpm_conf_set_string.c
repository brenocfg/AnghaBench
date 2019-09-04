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

/* Variables and functions */
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int fpm_conf_expand_pool_name (char**) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static char *fpm_conf_set_string(zval *value, void **config, intptr_t offset) /* {{{ */
{
	char **config_val = (char **) ((char *) *config + offset);

	if (!config_val) {
		return "internal error: NULL value";
	}

	/* Check if there is a previous value to deallocate */
	if (*config_val) {
		free(*config_val);
	}

	*config_val = strdup(Z_STRVAL_P(value));
	if (!*config_val) {
		return "fpm_conf_set_string(): strdup() failed";
	}
	if (fpm_conf_expand_pool_name(config_val) == -1) {
		return "Can't use '$pool' when the pool is not defined";
	}

	return NULL;
}