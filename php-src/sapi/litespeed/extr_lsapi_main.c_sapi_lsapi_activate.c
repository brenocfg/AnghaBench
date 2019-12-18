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
struct TYPE_2__ {char* path_translated; } ;

/* Variables and functions */
 char DEFAULT_SLASH ; 
 int FAILURE ; 
 int /*<<< orphan*/  IS_SLASH (char) ; 
 TYPE_1__ SG (int /*<<< orphan*/ ) ; 
 int SUCCESS ; 
 int /*<<< orphan*/  efree (char*) ; 
 char* emalloc (size_t) ; 
 char* estrndup (char*,size_t) ; 
 int lsapi_activate_user_ini () ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 scalar_t__ parse_user_ini ; 
 int /*<<< orphan*/  php_ini_activate_per_dir_config (char*,size_t) ; 
 int /*<<< orphan*/  php_ini_activate_per_host_config (char*,size_t) ; 
 scalar_t__ php_ini_has_per_dir_config () ; 
 scalar_t__ php_ini_has_per_host_config () ; 
 int /*<<< orphan*/  request_info ; 
 char* sapi_lsapi_getenv (char*,int /*<<< orphan*/ ) ; 
 size_t strlen (char*) ; 
 size_t zend_dirname (char*,size_t) ; 
 int /*<<< orphan*/  zend_str_tolower (char*,size_t) ; 

__attribute__((used)) static int sapi_lsapi_activate()
{
    char *path, *server_name;
    size_t path_len, server_name_len;

    /* PATH_TRANSLATED should be defined at this stage but better safe than sorry :) */
    if (!SG(request_info).path_translated) {
            return FAILURE;
    }

    if (php_ini_has_per_host_config()) {
        server_name = sapi_lsapi_getenv("SERVER_NAME", 0);
        /* SERVER_NAME should also be defined at this stage..but better check it anyway */
        if (server_name) {
                server_name_len = strlen(server_name);
                server_name = estrndup(server_name, server_name_len);
                zend_str_tolower(server_name, server_name_len);
                php_ini_activate_per_host_config(server_name, server_name_len);
                efree(server_name);
        }
    }

    if (php_ini_has_per_dir_config()) {
        /* Prepare search path */
        path_len = strlen(SG(request_info).path_translated);

        /* Make sure we have trailing slash! */
        if (!IS_SLASH(SG(request_info).path_translated[path_len])) {
            path = emalloc(path_len + 2);
            memcpy(path, SG(request_info).path_translated, path_len + 1);
            path_len = zend_dirname(path, path_len);
            path[path_len++] = DEFAULT_SLASH;
        } else {
            path = estrndup(SG(request_info).path_translated, path_len);
            path_len = zend_dirname(path, path_len);
        }
        path[path_len] = 0;

        /* Activate per-dir-system-configuration defined in php.ini and stored into configuration_hash during startup */
        php_ini_activate_per_dir_config(path, path_len); /* Note: for global settings sake we check from root to path */

        efree(path);
    }

    if (parse_user_ini && lsapi_activate_user_ini() == FAILURE) {
        return FAILURE;
    }
    return SUCCESS;
}