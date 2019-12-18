#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {int /*<<< orphan*/  function_table; } ;
struct TYPE_4__ {int count; int /*<<< orphan*/ * hosts; int /*<<< orphan*/ * redis; } ;
typedef  TYPE_1__ RedisArray ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_assoc_zval_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ra_call_user_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_2__* redis_array_ce ; 

__attribute__((used)) static void
multihost_distribute_call(RedisArray *ra, zval *return_value, zval *z_fun, int argc, zval *argv)
{
    zval z_tmp;
    int i;

    /* Init our array return */
    array_init(return_value);

    /* Iterate our RedisArray nodes */
    for (i = 0; i < ra->count; ++i) {
        /* Call each node in turn */
        ra_call_user_function(&redis_array_ce->function_table, &ra->redis[i], z_fun, &z_tmp, argc, argv);

        /* Add the result for this host */
        add_assoc_zval_ex(return_value, ZSTR_VAL(ra->hosts[i]), ZSTR_LEN(ra->hosts[i]), &z_tmp);
    }
}