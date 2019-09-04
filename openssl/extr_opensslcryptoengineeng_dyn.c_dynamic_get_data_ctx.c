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
typedef  int /*<<< orphan*/  dynamic_data_ctx ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_F_DYNAMIC_GET_DATA_CTX ; 
 int /*<<< orphan*/  ENGINE_R_NO_INDEX ; 
 scalar_t__ ENGINE_get_ex_data (int /*<<< orphan*/ *,int) ; 
 int ENGINE_get_ex_new_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dynamic_data_ctx_free_func ; 
 int dynamic_ex_data_idx ; 
 int /*<<< orphan*/  dynamic_set_data_ctx (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  global_engine_lock ; 

__attribute__((used)) static dynamic_data_ctx *dynamic_get_data_ctx(ENGINE *e)
{
    dynamic_data_ctx *ctx;
    if (dynamic_ex_data_idx < 0) {
        /*
         * Create and register the ENGINE ex_data, and associate our "free"
         * function with it to ensure any allocated contexts get freed when
         * an ENGINE goes underground.
         */
        int new_idx = ENGINE_get_ex_new_index(0, NULL, NULL, NULL,
                                              dynamic_data_ctx_free_func);
        if (new_idx == -1) {
            ENGINEerr(ENGINE_F_DYNAMIC_GET_DATA_CTX, ENGINE_R_NO_INDEX);
            return NULL;
        }
        CRYPTO_THREAD_write_lock(global_engine_lock);
        /* Avoid a race by checking again inside this lock */
        if (dynamic_ex_data_idx < 0) {
            /* Good, someone didn't beat us to it */
            dynamic_ex_data_idx = new_idx;
            new_idx = -1;
        }
        CRYPTO_THREAD_unlock(global_engine_lock);
        /*
         * In theory we could "give back" the index here if (new_idx>-1), but
         * it's not possible and wouldn't gain us much if it were.
         */
    }
    ctx = (dynamic_data_ctx *)ENGINE_get_ex_data(e, dynamic_ex_data_idx);
    /* Check if the context needs to be created */
    if ((ctx == NULL) && !dynamic_set_data_ctx(e, &ctx))
        /* "set_data" will set errors if necessary */
        return NULL;
    return ctx;
}