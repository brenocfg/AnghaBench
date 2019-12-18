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
struct TYPE_6__ {struct TYPE_6__* algs; int /*<<< orphan*/ * lock; int /*<<< orphan*/ * ctx; } ;
typedef  TYPE_1__ OSSL_METHOD_STORE ;
typedef  int /*<<< orphan*/  OPENSSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 TYPE_1__* ossl_sa_ALGORITHM_new () ; 

OSSL_METHOD_STORE *ossl_method_store_new(OPENSSL_CTX *ctx)
{
    OSSL_METHOD_STORE *res;

    res = OPENSSL_zalloc(sizeof(*res));
    if (res != NULL) {
        res->ctx = ctx;
        if ((res->algs = ossl_sa_ALGORITHM_new()) == NULL) {
            OPENSSL_free(res);
            return NULL;
        }
        if ((res->lock = CRYPTO_THREAD_lock_new()) == NULL) {
            OPENSSL_free(res->algs);
            OPENSSL_free(res);
            return NULL;
        }
    }
    return res;
}