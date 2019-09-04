#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int flags; int /*<<< orphan*/  p; int /*<<< orphan*/ * priv_key; TYPE_1__* meth; int /*<<< orphan*/  lock; int /*<<< orphan*/  method_mont_p; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* bn_mod_exp ) (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ DH ;
typedef  int /*<<< orphan*/  BN_MONT_CTX ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/ * BN_MONT_CTX_set_locked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int BN_bn2bin (int /*<<< orphan*/ *,unsigned char*) ; 
 scalar_t__ BN_num_bits (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DH_FLAG_CACHE_MONT_P ; 
 int /*<<< orphan*/  DH_F_COMPUTE_KEY ; 
 int /*<<< orphan*/  DH_R_INVALID_PUBKEY ; 
 int /*<<< orphan*/  DH_R_MODULUS_TOO_LARGE ; 
 int /*<<< orphan*/  DH_R_NO_PRIVATE_VALUE ; 
 int /*<<< orphan*/  DH_check_pub_key (TYPE_2__*,int /*<<< orphan*/  const*,int*) ; 
 int /*<<< orphan*/  DHerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 scalar_t__ OPENSSL_DH_MAX_MODULUS_BITS ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int compute_key(unsigned char *key, const BIGNUM *pub_key, DH *dh)
{
    BN_CTX *ctx = NULL;
    BN_MONT_CTX *mont = NULL;
    BIGNUM *tmp;
    int ret = -1;
    int check_result;

    if (BN_num_bits(dh->p) > OPENSSL_DH_MAX_MODULUS_BITS) {
        DHerr(DH_F_COMPUTE_KEY, DH_R_MODULUS_TOO_LARGE);
        goto err;
    }

    ctx = BN_CTX_new();
    if (ctx == NULL)
        goto err;
    BN_CTX_start(ctx);
    tmp = BN_CTX_get(ctx);
    if (tmp == NULL)
        goto err;

    if (dh->priv_key == NULL) {
        DHerr(DH_F_COMPUTE_KEY, DH_R_NO_PRIVATE_VALUE);
        goto err;
    }

    if (dh->flags & DH_FLAG_CACHE_MONT_P) {
        mont = BN_MONT_CTX_set_locked(&dh->method_mont_p,
                                      dh->lock, dh->p, ctx);
        BN_set_flags(dh->priv_key, BN_FLG_CONSTTIME);
        if (!mont)
            goto err;
    }

    if (!DH_check_pub_key(dh, pub_key, &check_result) || check_result) {
        DHerr(DH_F_COMPUTE_KEY, DH_R_INVALID_PUBKEY);
        goto err;
    }

    if (!dh->
        meth->bn_mod_exp(dh, tmp, pub_key, dh->priv_key, dh->p, ctx, mont)) {
        DHerr(DH_F_COMPUTE_KEY, ERR_R_BN_LIB);
        goto err;
    }

    ret = BN_bn2bin(tmp, key);
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    return ret;
}