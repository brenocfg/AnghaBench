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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  prov; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ EVP_SIGNATURE ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_provider_free (int /*<<< orphan*/ ) ; 

void EVP_SIGNATURE_free(EVP_SIGNATURE *signature)
{
    if (signature != NULL) {
        int i;

        CRYPTO_DOWN_REF(&signature->refcnt, &i, signature->lock);
        if (i > 0)
            return;
        ossl_provider_free(signature->prov);
        CRYPTO_THREAD_lock_free(signature->lock);
        OPENSSL_free(signature);
    }
}