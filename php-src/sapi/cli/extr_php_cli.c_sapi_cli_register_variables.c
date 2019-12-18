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
struct TYPE_2__ {scalar_t__ (* input_filter ) (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PARSE_SERVER ; 
 int /*<<< orphan*/  php_import_environment_variables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_register_variable (char*,char*,int /*<<< orphan*/ *) ; 
 char* php_self ; 
 TYPE_1__ sapi_module ; 
 char* script_filename ; 
 size_t strlen (char*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ; 
 scalar_t__ stub3 (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ; 
 scalar_t__ stub4 (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ; 
 scalar_t__ stub5 (int /*<<< orphan*/ ,char*,char**,size_t,size_t*) ; 

__attribute__((used)) static void sapi_cli_register_variables(zval *track_vars_array) /* {{{ */
{
	size_t len;
	char   *docroot = "";

	/* In CGI mode, we consider the environment to be a part of the server
	 * variables
	 */
	php_import_environment_variables(track_vars_array);

	/* Build the special-case PHP_SELF variable for the CLI version */
	len = strlen(php_self);
	if (sapi_module.input_filter(PARSE_SERVER, "PHP_SELF", &php_self, len, &len)) {
		php_register_variable("PHP_SELF", php_self, track_vars_array);
	}
	if (sapi_module.input_filter(PARSE_SERVER, "SCRIPT_NAME", &php_self, len, &len)) {
		php_register_variable("SCRIPT_NAME", php_self, track_vars_array);
	}
	/* filenames are empty for stdin */
	len = strlen(script_filename);
	if (sapi_module.input_filter(PARSE_SERVER, "SCRIPT_FILENAME", &script_filename, len, &len)) {
		php_register_variable("SCRIPT_FILENAME", script_filename, track_vars_array);
	}
	if (sapi_module.input_filter(PARSE_SERVER, "PATH_TRANSLATED", &script_filename, len, &len)) {
		php_register_variable("PATH_TRANSLATED", script_filename, track_vars_array);
	}
	/* just make it available */
	len = 0U;
	if (sapi_module.input_filter(PARSE_SERVER, "DOCUMENT_ROOT", &docroot, len, &len)) {
		php_register_variable("DOCUMENT_ROOT", docroot, track_vars_array);
	}
}