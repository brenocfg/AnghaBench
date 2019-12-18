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
struct TYPE_3__ {int /*<<< orphan*/  p; int /*<<< orphan*/ * q; } ;
typedef  TYPE_1__ DH ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_is_one (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_mod_exp (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_word (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_sub_word (int /*<<< orphan*/ *,int) ; 
 int DH_CHECK_PUBKEY_INVALID ; 
 int DH_CHECK_PUBKEY_TOO_LARGE ; 
 int DH_CHECK_PUBKEY_TOO_SMALL ; 

int DH_check_pub_key(const DH *dh, const BIGNUM *pub_key, int *ret)
{
    int ok = 0;
    BIGNUM *tmp = NULL;
    BN_CTX *ctx = NULL;

    *ret = 0;
    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;
    BN_CTX_start(ctx);
    tmp = BN_CTX_get(ctx);
    if (tmp == NULL || !BN_set_word(tmp, 1))
        goto err;
    if (BN_cmp(pub_key, tmp) <= 0)
        *ret |= DH_CHECK_PUBKEY_TOO_SMALL;
    if (BN_copy(tmp, dh->p) == NULL || !BN_sub_word(tmp, 1))
        goto err;
    if (BN_cmp(pub_key, tmp) >= 0)
        *ret |= DH_CHECK_PUBKEY_TOO_LARGE;

    if (dh->q != NULL) {
        /* Check pub_key^q == 1 mod p */
        if (!BN_mod_exp(tmp, pub_key, dh->q, dh->p, ctx))
            goto err;
        if (!BN_is_one(tmp))
            *ret |= DH_CHECK_PUBKEY_INVALID;
    }

    ok = 1;
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ok;
}