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
struct TYPE_3__ {int /*<<< orphan*/  piles; } ;
typedef  TYPE_1__ ENGINE_TABLE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  global_engine_lock ; 
 int /*<<< orphan*/  int_cleanup_cb_doall ; 
 int /*<<< orphan*/  lh_ENGINE_PILE_doall (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lh_ENGINE_PILE_free (int /*<<< orphan*/ *) ; 

void engine_table_cleanup(ENGINE_TABLE **table)
{
    CRYPTO_THREAD_write_lock(global_engine_lock);
    if (*table) {
        lh_ENGINE_PILE_doall(&(*table)->piles, int_cleanup_cb_doall);
        lh_ENGINE_PILE_free(&(*table)->piles);
        *table = NULL;
    }
    CRYPTO_THREAD_unlock(global_engine_lock);
}