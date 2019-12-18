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
struct TYPE_6__ {int /*<<< orphan*/  libctx; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_generate_dsa_nonce (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned char const*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_new () ; 
 int /*<<< orphan*/  BN_nnmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_priv_rand_range_ex (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_secure_new () ; 
 int /*<<< orphan*/  BN_set_bit (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  EC_F_ECDSA_SIGN_SETUP ; 
 int /*<<< orphan*/ * EC_GROUP_get0_order (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_can_sign (TYPE_1__*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (TYPE_1__*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_private_key (TYPE_1__*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING ; 
 int /*<<< orphan*/  EC_R_MISSING_PRIVATE_KEY ; 
 int /*<<< orphan*/  EC_R_RANDOM_NUMBER_GENERATION_FAILED ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int /*<<< orphan*/  ec_group_do_inverse_ord (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ecdsa_sign_setup(EC_KEY *eckey, BN_CTX *ctx_in,
                            BIGNUM **kinvp, BIGNUM **rp,
                            const unsigned char *dgst, int dlen)
{
    BN_CTX *ctx = NULL;
    BIGNUM *k = NULL, *r = NULL, *X = NULL;
    const BIGNUM *order;
    EC_POINT *tmp_point = NULL;
    const EC_GROUP *group;
    int ret = 0;
    int order_bits;
    const BIGNUM *priv_key;

    if (eckey == NULL || (group = EC_KEY_get0_group(eckey)) == NULL) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }
    if ((priv_key = EC_KEY_get0_private_key(eckey)) == NULL) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, EC_R_MISSING_PRIVATE_KEY);
        return 0;
    }

    if (!EC_KEY_can_sign(eckey)) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING);
        return 0;
    }

    if ((ctx = ctx_in) == NULL) {
        if ((ctx = BN_CTX_new_ex(eckey->libctx)) == NULL) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_MALLOC_FAILURE);
            return 0;
        }
    }

    k = BN_secure_new();        /* this value is later returned in *kinvp */
    r = BN_new();               /* this value is later returned in *rp */
    X = BN_new();
    if (k == NULL || r == NULL || X == NULL) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if ((tmp_point = EC_POINT_new(group)) == NULL) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_EC_LIB);
        goto err;
    }
    order = EC_GROUP_get0_order(group);

    /* Preallocate space */
    order_bits = BN_num_bits(order);
    if (!BN_set_bit(k, order_bits)
        || !BN_set_bit(r, order_bits)
        || !BN_set_bit(X, order_bits))
        goto err;

    do {
        /* get random k */
        do {
            if (dgst != NULL) {
                if (!BN_generate_dsa_nonce(k, order, priv_key,
                                           dgst, dlen, ctx)) {
                    ECerr(EC_F_ECDSA_SIGN_SETUP,
                          EC_R_RANDOM_NUMBER_GENERATION_FAILED);
                    goto err;
                }
            } else {
                if (!BN_priv_rand_range_ex(k, order, ctx)) {
                    ECerr(EC_F_ECDSA_SIGN_SETUP,
                          EC_R_RANDOM_NUMBER_GENERATION_FAILED);
                    goto err;
                }
            }
        } while (BN_is_zero(k));

        /* compute r the x-coordinate of generator * k */
        if (!EC_POINT_mul(group, tmp_point, k, NULL, NULL, ctx)) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_EC_LIB);
            goto err;
        }

        if (!EC_POINT_get_affine_coordinates(group, tmp_point, X, NULL, ctx)) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_EC_LIB);
            goto err;
        }

        if (!BN_nnmod(r, X, order, ctx)) {
            ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_BN_LIB);
            goto err;
        }
    } while (BN_is_zero(r));

    /* compute the inverse of k */
    if (!ec_group_do_inverse_ord(group, k, k, ctx)) {
        ECerr(EC_F_ECDSA_SIGN_SETUP, ERR_R_BN_LIB);
        goto err;
    }

    /* clear old values if necessary */
    BN_clear_free(*rp);
    BN_clear_free(*kinvp);
    /* save the pre-computed values  */
    *rp = r;
    *kinvp = k;
    ret = 1;
 err:
    if (!ret) {
        BN_clear_free(k);
        BN_clear_free(r);
    }
    if (ctx != ctx_in)
        BN_CTX_free(ctx);
    EC_POINT_free(tmp_point);
    BN_clear_free(X);
    return ret;
}