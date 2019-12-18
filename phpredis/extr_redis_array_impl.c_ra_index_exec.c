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
struct TYPE_2__ {int /*<<< orphan*/  function_table; } ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  RETVAL_ZVAL (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  Z_ARRVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* redis_ce ; 
 int /*<<< orphan*/ * zend_hash_index_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

void
ra_index_exec(zval *z_redis, zval *return_value, int keep_all) {

    zval z_fun_exec, z_ret, *zp_tmp;

    /* run EXEC */
    ZVAL_STRINGL(&z_fun_exec, "EXEC", 4);
    ra_call_user_function(&redis_ce->function_table, z_redis, &z_fun_exec, &z_ret, 0, NULL);
    zval_dtor(&z_fun_exec);

    /* extract first element of exec array and put into return_value. */
    if(Z_TYPE(z_ret) == IS_ARRAY) {
        if(return_value) {
                if(keep_all) {
                    zp_tmp = &z_ret;
                    RETVAL_ZVAL(zp_tmp, 1, 0);
                } else if ((zp_tmp = zend_hash_index_find(Z_ARRVAL(z_ret), 0)) != NULL) {
                    RETVAL_ZVAL(zp_tmp, 1, 0);
                }
        }
    }
    zval_dtor(&z_ret);

    /* zval *zptr = &z_ret; */
    /* php_var_dump(&zptr, 0); */
}