#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {char* c; int len; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ smart_string ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 int FAILURE ; 
#define  IS_DOUBLE 130 
#define  IS_LONG 129 
#define  IS_STRING 128 
 int SUCCESS ; 
 int /*<<< orphan*/  Z_DVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_LVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRLEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_STRVAL (int /*<<< orphan*/ ) ; 
 int Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (char*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  redis_cmd_append_sstr (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redis_cmd_append_sstr_dbl (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redis_cmd_append_sstr_long (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  redis_cmd_init_sstr (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int redis_build_raw_cmd(zval *z_args, int argc, char **cmd, int *cmd_len)
{
    smart_string cmdstr = {0};
    int i;

    /* Make sure our first argument is a string */
    if (Z_TYPE(z_args[0]) != IS_STRING) {
        php_error_docref(NULL, E_WARNING,
            "When sending a 'raw' command, the first argument must be a string!");
        return FAILURE;
    }

    /* Initialize our command string */
    redis_cmd_init_sstr(&cmdstr, argc-1, Z_STRVAL(z_args[0]), Z_STRLEN(z_args[0]));

    for (i = 1; i < argc; i++) {
       switch (Z_TYPE(z_args[i])) {
            case IS_STRING:
                redis_cmd_append_sstr(&cmdstr, Z_STRVAL(z_args[i]),
                    Z_STRLEN(z_args[i]));
                break;
            case IS_LONG:
                redis_cmd_append_sstr_long(&cmdstr,Z_LVAL(z_args[i]));
                break;
            case IS_DOUBLE:
                redis_cmd_append_sstr_dbl(&cmdstr,Z_DVAL(z_args[i]));
                break;
            default:
                php_error_docref(NULL, E_WARNING,
                    "Raw command arguments must be scalar values!");
                efree(cmdstr.c);
                return FAILURE;
        }
    }

    /* Push command and length to caller */
    *cmd = cmdstr.c;
    *cmd_len = cmdstr.len;

    return SUCCESS;
}