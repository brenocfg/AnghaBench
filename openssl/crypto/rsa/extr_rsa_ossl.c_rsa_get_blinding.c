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
struct TYPE_4__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * mt_blinding; int /*<<< orphan*/ * blinding; } ;
typedef  TYPE_1__ RSA ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BN_BLINDING ;

/* Variables and functions */
 scalar_t__ BN_BLINDING_is_current_thread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CRYPTO_THREAD_write_lock (int /*<<< orphan*/ ) ; 
 void* RSA_setup_blinding (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static BN_BLINDING *rsa_get_blinding(RSA *rsa, int *local, BN_CTX *ctx)
{
    BN_BLINDING *ret;

    CRYPTO_THREAD_write_lock(rsa->lock);

    if (rsa->blinding == NULL) {
        rsa->blinding = RSA_setup_blinding(rsa, ctx);
    }

    ret = rsa->blinding;
    if (ret == NULL)
        goto err;

    if (BN_BLINDING_is_current_thread(ret)) {
        /* rsa->blinding is ours! */

        *local = 1;
    } else {
        /* resort to rsa->mt_blinding instead */

        /*
         * instructs rsa_blinding_convert(), rsa_blinding_invert() that the
         * BN_BLINDING is shared, meaning that accesses require locks, and
         * that the blinding factor must be stored outside the BN_BLINDING
         */
        *local = 0;

        if (rsa->mt_blinding == NULL) {
            rsa->mt_blinding = RSA_setup_blinding(rsa, ctx);
        }
        ret = rsa->mt_blinding;
    }

 err:
    CRYPTO_THREAD_unlock(rsa->lock);
    return ret;
}