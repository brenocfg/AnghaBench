#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int counter; int /*<<< orphan*/ * mod; int /*<<< orphan*/ * Ai; int /*<<< orphan*/ * A; int /*<<< orphan*/ * lock; } ;
typedef  TYPE_1__ BN_BLINDING ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_BLINDING_free (TYPE_1__*) ; 
 int /*<<< orphan*/  BN_BLINDING_set_current_thread (TYPE_1__*) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_F_BN_BLINDING_NEW ; 
 void* BN_dup (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_get_flags (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CRYPTO_THREAD_lock_new () ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (TYPE_1__*) ; 
 TYPE_1__* OPENSSL_zalloc (int) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/  const*) ; 

BN_BLINDING *BN_BLINDING_new(const BIGNUM *A, const BIGNUM *Ai, BIGNUM *mod)
{
    BN_BLINDING *ret = NULL;

    bn_check_top(mod);

    if ((ret = OPENSSL_zalloc(sizeof(*ret))) == NULL) {
        BNerr(BN_F_BN_BLINDING_NEW, ERR_R_MALLOC_FAILURE);
        return NULL;
    }

    ret->lock = CRYPTO_THREAD_lock_new();
    if (ret->lock == NULL) {
        BNerr(BN_F_BN_BLINDING_NEW, ERR_R_MALLOC_FAILURE);
        OPENSSL_free(ret);
        return NULL;
    }

    BN_BLINDING_set_current_thread(ret);

    if (A != NULL) {
        if ((ret->A = BN_dup(A)) == NULL)
            goto err;
    }

    if (Ai != NULL) {
        if ((ret->Ai = BN_dup(Ai)) == NULL)
            goto err;
    }

    /* save a copy of mod in the BN_BLINDING structure */
    if ((ret->mod = BN_dup(mod)) == NULL)
        goto err;

    if (BN_get_flags(mod, BN_FLG_CONSTTIME) != 0)
        BN_set_flags(ret->mod, BN_FLG_CONSTTIME);

    /*
     * Set the counter to the special value -1 to indicate that this is
     * never-used fresh blinding that does not need updating before first
     * use.
     */
    ret->counter = -1;

    return ret;

 err:
    BN_BLINDING_free(ret);
    return NULL;
}