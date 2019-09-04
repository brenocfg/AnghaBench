#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* DYNAMIC_F1; char* DYNAMIC_F2; int dir_load; int /*<<< orphan*/ * dirs; } ;
typedef  TYPE_1__ dynamic_data_ctx ;
typedef  int /*<<< orphan*/  ENGINE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENGINE_F_DYNAMIC_SET_DATA_CTX ; 
 scalar_t__ ENGINE_get_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ENGINE_set_ex_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ENGINEerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  dynamic_ex_data_idx ; 
 int /*<<< orphan*/  global_engine_lock ; 
 int /*<<< orphan*/  sk_OPENSSL_STRING_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sk_OPENSSL_STRING_new_null () ; 

__attribute__((used)) static int dynamic_set_data_ctx(ENGINE *e, dynamic_data_ctx **ctx)
{
    dynamic_data_ctx *c = OPENSSL_zalloc(sizeof(*c));
    int ret = 1;

    if (c == NULL) {
        ENGINEerr(ENGINE_F_DYNAMIC_SET_DATA_CTX, ERR_R_MALLOC_FAILURE);
        return 0;
    }
    c->dirs = sk_OPENSSL_STRING_new_null();
    if (c->dirs == NULL) {
        ENGINEerr(ENGINE_F_DYNAMIC_SET_DATA_CTX, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(c);
        return 0;
    }
    c->DYNAMIC_F1 = "v_check";
    c->DYNAMIC_F2 = "bind_engine";
    c->dir_load = 1;
    CRYPTO_THREAD_write_lock(global_engine_lock);
    if ((*ctx = (dynamic_data_ctx *)ENGINE_get_ex_data(e,
                                                       dynamic_ex_data_idx))
        == NULL) {
        /* Good, we're the first */
        ret = ENGINE_set_ex_data(e, dynamic_ex_data_idx, c);
        if (ret) {
            *ctx = c;
            c = NULL;
        }
    }
    CRYPTO_THREAD_unlock(global_engine_lock);
    /*
     * If we lost the race to set the context, c is non-NULL and *ctx is the
     * context of the thread that won.
     */
    if (c)
        sk_OPENSSL_STRING_free(c->dirs);
    OPENSSL_free(c);
    return ret;
}