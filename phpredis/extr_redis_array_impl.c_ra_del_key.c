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
 int /*<<< orphan*/  MULTI ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  ra_call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_index_exec (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_index_multi (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ra_remove_from_index (int /*<<< orphan*/ *,char const*,int) ; 
 TYPE_1__* redis_ce ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool
ra_del_key(const char *key, int key_len, zval *z_from) {

    zval z_fun_del, z_ret, z_args[1];

    /* in a transaction */
    ra_index_multi(z_from, MULTI);

    /* run DEL on source */
    ZVAL_STRINGL(&z_fun_del, "DEL", 3);
    ZVAL_STRINGL(&z_args[0], key, key_len);
    ra_call_user_function(&redis_ce->function_table, z_from, &z_fun_del, &z_ret, 1, z_args);
    zval_dtor(&z_fun_del);
    zval_dtor(&z_args[0]);
    zval_dtor(&z_ret);

    /* remove key from index */
    ra_remove_from_index(z_from, key, key_len);

    /* close transaction */
    ra_index_exec(z_from, NULL, 0);

    return 1;
}