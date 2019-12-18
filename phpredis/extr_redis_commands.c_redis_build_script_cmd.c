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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  smart_string ;

/* Variables and functions */
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  REDIS_CMD_INIT_SSTR_STATIC (int /*<<< orphan*/ *,int,char*) ; 
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int Z_STRLEN (int /*<<< orphan*/ ) ; 
 char* Z_STRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redis_cmd_append_sstr (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_string (int /*<<< orphan*/ *) ; 

smart_string *
redis_build_script_cmd(smart_string *cmd, int argc, zval *z_args)
{
    int i;
    zend_string *zstr;

    if (Z_TYPE(z_args[0]) != IS_STRING) {
        return NULL;
    }
    // Branch based on the directive
    if (!strcasecmp(Z_STRVAL(z_args[0]), "flush") || !strcasecmp(Z_STRVAL(z_args[0]), "kill")) {
        // Simple SCRIPT FLUSH, or SCRIPT_KILL command
        REDIS_CMD_INIT_SSTR_STATIC(cmd, argc, "SCRIPT");
        redis_cmd_append_sstr(cmd, Z_STRVAL(z_args[0]), Z_STRLEN(z_args[0]));
    } else if (!strcasecmp(Z_STRVAL(z_args[0]), "load")) {
        // Make sure we have a second argument, and it's not empty.  If it is
        // empty, we can just return an empty array (which is what Redis does)
        if (argc < 2 || Z_TYPE(z_args[1]) != IS_STRING || Z_STRLEN(z_args[1]) < 1) {
            return NULL;
        }
        // Format our SCRIPT LOAD command
        REDIS_CMD_INIT_SSTR_STATIC(cmd, argc, "SCRIPT");
        redis_cmd_append_sstr(cmd, "LOAD", sizeof("LOAD") - 1);
        redis_cmd_append_sstr(cmd, Z_STRVAL(z_args[1]), Z_STRLEN(z_args[1]));
    } else if (!strcasecmp(Z_STRVAL(z_args[0]), "exists")) {
        // Make sure we have a second argument
        if (argc < 2) {
            return NULL;
        }
        /* Construct our SCRIPT EXISTS command */
        REDIS_CMD_INIT_SSTR_STATIC(cmd, argc, "SCRIPT");
        redis_cmd_append_sstr(cmd, "EXISTS", sizeof("EXISTS") - 1);

        for (i = 1; i < argc; ++i) {
            zstr = zval_get_string(&z_args[i]);
            redis_cmd_append_sstr(cmd, ZSTR_VAL(zstr), ZSTR_LEN(zstr));
            zend_string_release(zstr);
        }
    } else {
        /* Unknown directive */
        return NULL;
    }
    return cmd;
}