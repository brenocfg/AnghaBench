#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  piles; } ;
typedef  TYPE_1__ ENGINE_TABLE ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_engine_lock ; 
 scalar_t__ int_table_check (TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  int_unregister_cb ; 
 int /*<<< orphan*/  lh_ENGINE_PILE_doall_ENGINE (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void engine_table_unregister(ENGINE_TABLE **table, ENGINE *e)
{
    CRYPTO_THREAD_write_lock(global_engine_lock);
    if (int_table_check(table, 0))
        lh_ENGINE_PILE_doall_ENGINE(&(*table)->piles, int_unregister_cb, e);
    CRYPTO_THREAD_unlock(global_engine_lock);
}