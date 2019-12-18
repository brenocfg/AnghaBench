#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int refcnt; int /*<<< orphan*/ * prov; int /*<<< orphan*/ * lock; } ;
typedef  int /*<<< orphan*/  OSSL_PROVIDER ;
typedef  TYPE_1__ EVP_SIGNATURE ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  ossl_provider_up_ref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static EVP_SIGNATURE *evp_signature_new(OSSL_PROVIDER *prov)
{
    EVP_SIGNATURE *signature = OPENSSL_zalloc(sizeof(EVP_SIGNATURE));

    signature->lock = CRYPTO_THREAD_lock_new();
    if (signature->lock == NULL) {
        OPENSSL_free(signature);
        return NULL;
    }
    signature->prov = prov;
    ossl_provider_up_ref(prov);
    signature->refcnt = 1;

    return signature;
}