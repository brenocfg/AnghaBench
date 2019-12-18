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
struct TYPE_5__ {int refcnt; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ EVP_CIPHER ;

/* Variables and functions */
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 

EVP_CIPHER *evp_cipher_new(void)
{
    EVP_CIPHER *cipher = OPENSSL_zalloc(sizeof(EVP_CIPHER));

    if (cipher != NULL) {
        cipher->lock = CRYPTO_THREAD_lock_new();
        if (cipher->lock == NULL) {
            OPENSSL_free(cipher);
            return NULL;
        }
        cipher->refcnt = 1;
    }
    return cipher;
}