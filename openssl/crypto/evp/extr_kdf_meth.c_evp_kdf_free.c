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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  prov; int /*<<< orphan*/  refcnt; } ;
typedef  TYPE_1__ EVP_KDF ;

/* Variables and functions */
 int /*<<< orphan*/  CRYPTO_DOWN_REF (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_lock_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ossl_provider_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void evp_kdf_free(void *vkdf){
    EVP_KDF *kdf = (EVP_KDF *)vkdf;
    int ref = 0;

    if (kdf != NULL) {
        CRYPTO_DOWN_REF(&kdf->refcnt, &ref, kdf->lock);
        if (ref <= 0) {
            ossl_provider_free(kdf->prov);
            CRYPTO_THREAD_lock_free(kdf->lock);
            OPENSSL_free(kdf);
        }
    }
}