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
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  ra_call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* redis_ce ; 
 int /*<<< orphan*/  zval_dtor (int /*<<< orphan*/ *) ; 

void
ra_index_discard(zval *z_redis, zval *return_value) {

    zval z_fun_discard, z_ret;

    /* run DISCARD */
    ZVAL_STRINGL(&z_fun_discard, "DISCARD", 7);
    ra_call_user_function(&redis_ce->function_table, z_redis, &z_fun_discard, &z_ret, 0, NULL);

    zval_dtor(&z_fun_discard);
    zval_dtor(&z_ret);
}