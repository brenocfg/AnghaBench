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
struct TYPE_6__ {scalar_t__ blocked; int /*<<< orphan*/ * currjob; int /*<<< orphan*/  dispatcher; } ;
typedef  TYPE_1__ async_ctx ;

/* Variables and functions */
 int /*<<< orphan*/  ASYNC_F_ASYNC_CTX_NEW ; 
 int /*<<< orphan*/  ASYNCerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  async_delete_thread_state ; 
 int /*<<< orphan*/  async_fibre_init_dispatcher (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctxkey ; 
 int /*<<< orphan*/  ossl_init_thread_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static async_ctx *async_ctx_new(void)
{
    async_ctx *nctx;

    if (!ossl_init_thread_start(NULL, NULL, async_delete_thread_state))
        return NULL;

    nctx = OPENSSL_malloc(sizeof(*nctx));
    if (nctx == NULL) {
        ASYNCerr(ASYNC_F_ASYNC_CTX_NEW, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    async_fibre_init_dispatcher(&nctx->dispatcher);
    nctx->currjob = NULL;
    nctx->blocked = 0;
    if (!CRYPTO_THREAD_set_local(&ctxkey, nctx))
        goto err;

    return nctx;
err:
    OPENSSL_free(nctx);

    return NULL;
}