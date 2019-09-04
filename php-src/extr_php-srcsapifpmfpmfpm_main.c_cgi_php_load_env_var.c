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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_2__ {scalar_t__ (* input_filter ) (int,char*,char**,int /*<<< orphan*/ ,size_t*) ;} ;

/* Variables and functions */
 int PARSE_ENV ; 
 int PARSE_SERVER ; 
 int /*<<< orphan*/ * PG (int /*<<< orphan*/ ) ; 
 size_t TRACK_VARS_ENV ; 
 scalar_t__ Z_ARR (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ARR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  http_globals ; 
 int /*<<< orphan*/  php_register_variable_safe (char*,char*,size_t,int /*<<< orphan*/ *) ; 
 TYPE_1__ sapi_module ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ stub1 (int,char*,char**,int /*<<< orphan*/ ,size_t*) ; 

__attribute__((used)) static void cgi_php_load_env_var(char *var, unsigned int var_len, char *val, unsigned int val_len, void *arg) /* {{{ */
{
	zval *array_ptr = (zval*)arg;
	int filter_arg = (Z_ARR_P(array_ptr) == Z_ARR(PG(http_globals)[TRACK_VARS_ENV]))?PARSE_ENV:PARSE_SERVER;
	size_t new_val_len;

	if (sapi_module.input_filter(filter_arg, var, &val, strlen(val), &new_val_len)) {
		php_register_variable_safe(var, val, new_val_len, array_ptr);
	}
}