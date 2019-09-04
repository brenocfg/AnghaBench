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
 char* Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int atoi (char*) ; 

__attribute__((used)) static char *fpm_conf_set_integer(zval *value, void **config, intptr_t offset) /* {{{ */
{
	char *val = Z_STRVAL_P(value);
	char *p;

	/* we don't use strtol because we don't want to allow negative values */
	for (p = val; *p; p++) {
		if (p == val && *p == '-') continue;
		if (*p < '0' || *p > '9') {
			return "is not a valid number (greater or equal than zero)";
		}
	}
	* (int *) ((char *) *config + offset) = atoi(val);
	return NULL;
}