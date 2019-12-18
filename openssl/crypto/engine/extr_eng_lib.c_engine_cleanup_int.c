#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cleanup_stack ; 
 int /*<<< orphan*/  engine_cleanup_cb_free ; 
 int /*<<< orphan*/  global_engine_lock ; 
 scalar_t__ int_cleanup_check (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sk_ENGINE_CLEANUP_ITEM_pop_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void engine_cleanup_int(void)
{
    if (int_cleanup_check(0)) {
        sk_ENGINE_CLEANUP_ITEM_pop_free(cleanup_stack,
                                        engine_cleanup_cb_free);
        cleanup_stack = NULL;
    }
    CRYPTO_THREAD_lock_free(global_engine_lock);
}