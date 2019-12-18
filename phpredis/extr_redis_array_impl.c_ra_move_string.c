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
typedef  int zend_bool ;
struct TYPE_2__ {int /*<<< orphan*/  function_table; } ;

/* Variables and functions */
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char const*,int) ; 
 int Z_STRLEN (int /*<<< orphan*/ ) ; 
 char* Z_STRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* redis_ce ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool
ra_move_string(const char *key, int key_len, zval *z_from, zval *z_to, long ttl) {

    zval z_fun_get, z_fun_set, z_ret, z_args[3];

    /* run GET on source */
    ZVAL_STRINGL(&z_fun_get, "GET", 3);
    ZVAL_STRINGL(&z_args[0], key, key_len);
    ra_call_user_function(&redis_ce->function_table, z_from, &z_fun_get, &z_ret, 1, z_args);
    zval_dtor(&z_fun_get);

    if(Z_TYPE(z_ret) != IS_STRING) { /* key not found or replaced */
        /* TODO: report? */
        zval_dtor(&z_args[0]);
        zval_dtor(&z_ret);
        return 0;
    }

    /* run SET on target */
    if (ttl > 0) {
        ZVAL_STRINGL(&z_fun_set, "SETEX", 5);
        ZVAL_LONG(&z_args[1], ttl);
        ZVAL_STRINGL(&z_args[2], Z_STRVAL(z_ret), Z_STRLEN(z_ret)); /* copy z_ret to arg 1 */
        zval_dtor(&z_ret); /* free memory from our previous call */
        ra_call_user_function(&redis_ce->function_table, z_to, &z_fun_set, &z_ret, 3, z_args);
        /* cleanup */
        zval_dtor(&z_args[2]);
    } else {
        ZVAL_STRINGL(&z_fun_set, "SET", 3);
        ZVAL_STRINGL(&z_args[1], Z_STRVAL(z_ret), Z_STRLEN(z_ret)); /* copy z_ret to arg 1 */
        zval_dtor(&z_ret); /* free memory from our previous return value */
        ra_call_user_function(&redis_ce->function_table, z_to, &z_fun_set, &z_ret, 2, z_args);
        /* cleanup */
        zval_dtor(&z_args[1]);
    }
    zval_dtor(&z_fun_set);
    zval_dtor(&z_args[0]);
    zval_dtor(&z_ret);

    return 1;
}