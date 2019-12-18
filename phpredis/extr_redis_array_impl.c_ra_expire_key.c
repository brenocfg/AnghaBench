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
 int /*<<< orphan*/  ZVAL_LONG (int /*<<< orphan*/ *,long) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ra_call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* redis_ce ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool
ra_expire_key(const char *key, int key_len, zval *z_to, long ttl) {

    zval z_fun_expire, z_ret, z_args[2];

    if (ttl > 0)
    {
        /* run EXPIRE on target */
        ZVAL_STRINGL(&z_fun_expire, "EXPIRE", 6);
        ZVAL_STRINGL(&z_args[0], key, key_len);
        ZVAL_LONG(&z_args[1], ttl);
        ra_call_user_function(&redis_ce->function_table, z_to, &z_fun_expire, &z_ret, 2, z_args);
        zval_dtor(&z_fun_expire);
        zval_dtor(&z_args[0]);
        zval_dtor(&z_ret);
    }

    return 1;
}