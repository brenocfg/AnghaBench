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
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_F_ENGINE_REMOVE ; 
 int /*<<< orphan*/  ENGINE_R_INTERNAL_LIST_ERROR ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  engine_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  global_engine_lock ; 

int ENGINE_remove(ENGINE *e)
{
    int to_return = 1;
    if (e == NULL) {
        ENGINEerr(ENGINE_F_ENGINE_REMOVE, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    CRYPTO_THREAD_write_lock(global_engine_lock);
    if (!engine_list_remove(e)) {
        ENGINEerr(ENGINE_F_ENGINE_REMOVE, ENGINE_R_INTERNAL_LIST_ERROR);
        to_return = 0;
    }
    CRYPTO_THREAD_unlock(global_engine_lock);
    return to_return;
}