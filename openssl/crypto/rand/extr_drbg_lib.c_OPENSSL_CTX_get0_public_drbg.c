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
struct TYPE_3__ {int /*<<< orphan*/  public_drbg; int /*<<< orphan*/  master_drbg; } ;
typedef  int /*<<< orphan*/  RAND_DRBG ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;
typedef  TYPE_1__ DRBG_GLOBAL ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_get_local (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_set_local (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RAND_DRBG_TYPE_PUBLIC ; 
 int /*<<< orphan*/  drbg_delete_thread_state ; 
 TYPE_1__* drbg_get_global (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * drbg_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * openssl_ctx_get_concrete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ossl_init_thread_start (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

RAND_DRBG *OPENSSL_CTX_get0_public_drbg(OPENSSL_CTX *ctx)
{
    DRBG_GLOBAL *dgbl = drbg_get_global(ctx);
    RAND_DRBG *drbg;

    if (dgbl == NULL)
        return NULL;

    drbg = CRYPTO_THREAD_get_local(&dgbl->public_drbg);
    if (drbg == NULL) {
        ctx = openssl_ctx_get_concrete(ctx);
        if (!ossl_init_thread_start(NULL, ctx, drbg_delete_thread_state))
            return NULL;
        drbg = drbg_setup(ctx, dgbl->master_drbg, RAND_DRBG_TYPE_PUBLIC);
        CRYPTO_THREAD_set_local(&dgbl->public_drbg, drbg);
    }
    return drbg;
}