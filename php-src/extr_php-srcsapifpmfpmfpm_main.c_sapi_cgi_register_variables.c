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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {char* request_uri; } ;
struct TYPE_3__ {scalar_t__ (* input_filter ) (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ;} ;

/* Variables and functions */
 scalar_t__ CGIG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PARSE_SERVER ; 
 TYPE_2__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 int /*<<< orphan*/  fix_pathinfo ; 
 int /*<<< orphan*/  memcpy (char*,char*,unsigned int) ; 
 int /*<<< orphan*/  php_import_environment_variables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_register_variable_safe (char*,char*,size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_info ; 
 char* sapi_cgibin_getenv (char*,int) ; 
 TYPE_1__ sapi_module ; 
 void* strlen (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ; 

__attribute__((used)) static void sapi_cgi_register_variables(zval *track_vars_array) /* {{{ */
{
	size_t php_self_len;
	char *php_self;

	/* In CGI mode, we consider the environment to be a part of the server
	 * variables
	 */
	php_import_environment_variables(track_vars_array);

	if (CGIG(fix_pathinfo)) {
		char *script_name = SG(request_info).request_uri;
		unsigned int script_name_len = script_name ? strlen(script_name) : 0;
		char *path_info = sapi_cgibin_getenv("PATH_INFO", sizeof("PATH_INFO") - 1);
		unsigned int path_info_len = path_info ? strlen(path_info) : 0;

		php_self_len = script_name_len + path_info_len;
		php_self = emalloc(php_self_len + 1);

		/* Concat script_name and path_info into php_self */
		if (script_name) {
			memcpy(php_self, script_name, script_name_len + 1);
		}
		if (path_info) {
			memcpy(php_self + script_name_len, path_info, path_info_len + 1);
		}

		/* Build the special-case PHP_SELF variable for the CGI version */
		if (sapi_module.input_filter(PARSE_SERVER, "PHP_SELF", &php_self, php_self_len, &php_self_len)) {
			php_register_variable_safe("PHP_SELF", php_self, php_self_len, track_vars_array);
		}
		efree(php_self);
	} else {
		php_self = SG(request_info).request_uri ? SG(request_info).request_uri : "";
		php_self_len = strlen(php_self);
		if (sapi_module.input_filter(PARSE_SERVER, "PHP_SELF", &php_self, php_self_len, &php_self_len)) {
			php_register_variable_safe("PHP_SELF", php_self, php_self_len, track_vars_array);
		}
	}
}