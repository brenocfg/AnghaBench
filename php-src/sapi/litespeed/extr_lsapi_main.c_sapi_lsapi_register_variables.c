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
struct TYPE_2__ {char* request_uri; } ;

/* Variables and functions */
 int /*<<< orphan*/  LSAPI_ForeachEnv (int /*<<< orphan*/  (*) (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LSAPI_ForeachHeader (int /*<<< orphan*/  (*) (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *),int /*<<< orphan*/ *) ; 
 TYPE_1__ SG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_variable (char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  litespeed_php_import_environment_variables (int /*<<< orphan*/ *) ; 
 scalar_t__ lsapi_mode ; 
 int /*<<< orphan*/  php_import_environment_variables (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_register_variable (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  request_info ; 
 char* script_filename ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static void sapi_lsapi_register_variables(zval *track_vars_array)
{
    char * php_self = "";
    if ( lsapi_mode ) {
        if ( (SG(request_info).request_uri ) )
            php_self = (SG(request_info).request_uri );

        litespeed_php_import_environment_variables(track_vars_array);

        LSAPI_ForeachHeader( add_variable, track_vars_array );
        LSAPI_ForeachEnv( add_variable, track_vars_array );
        add_variable("PHP_SELF", 8, php_self, strlen( php_self ), track_vars_array );
    } else {
        php_import_environment_variables(track_vars_array);

        php_register_variable("PHP_SELF", php_self, track_vars_array);
        php_register_variable("SCRIPT_NAME", php_self, track_vars_array);
        php_register_variable("SCRIPT_FILENAME", script_filename, track_vars_array);
        php_register_variable("PATH_TRANSLATED", script_filename, track_vars_array);
        php_register_variable("DOCUMENT_ROOT", "", track_vars_array);

    }
}