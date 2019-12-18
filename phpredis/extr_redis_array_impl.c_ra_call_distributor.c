#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int /*<<< orphan*/  z_dist; } ;
typedef  TYPE_1__ RedisArray ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_ERROR ; 
 scalar_t__ IS_LONG ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char const*,int) ; 
 int Z_LVAL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  function_table ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ra_call_user_function (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_is_callable_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

int
ra_call_distributor(RedisArray *ra, const char *key, int key_len)
{
    int ret;
    zval z_ret, z_argv;

    /* check that we can call the extractor function */
    if (!zend_is_callable_ex(&ra->z_dist, NULL, 0, NULL, NULL, NULL)) {
        php_error_docref(NULL, E_ERROR, "Could not call distributor function");
        return -1;
    }

    ZVAL_NULL(&z_ret);
    /* call extraction function */
    ZVAL_STRINGL(&z_argv, key, key_len);
    ra_call_user_function(EG(function_table), NULL, &ra->z_dist, &z_ret, 1, &z_argv);

    ret = (Z_TYPE(z_ret) == IS_LONG) ? Z_LVAL(z_ret) : -1;

    zval_dtor(&z_argv);
    zval_dtor(&z_ret);
    return ret;
}