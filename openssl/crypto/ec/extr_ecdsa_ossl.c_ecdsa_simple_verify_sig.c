#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  const* r; int /*<<< orphan*/  const* s; } ;
struct TYPE_8__ {int /*<<< orphan*/  libctx; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_KEY ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  TYPE_2__ ECDSA_SIG ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new_ex (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_bin2bn (unsigned char const*,int,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_mod_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_nnmod (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_rshift (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_F_ECDSA_SIMPLE_VERIFY_SIG ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_order (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_can_sign (TYPE_1__*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_group (TYPE_1__*) ; 
 int /*<<< orphan*/ * EC_KEY_get0_public_key (TYPE_1__*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_R_BAD_SIGNATURE ; 
 int /*<<< orphan*/  EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING ; 
 int /*<<< orphan*/  EC_R_MISSING_PARAMETERS ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ec_group_do_inverse_ord (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int ecdsa_simple_verify_sig(const unsigned char *dgst, int dgst_len,
                            const ECDSA_SIG *sig, EC_KEY *eckey)
{
    int ret = -1, i;
    BN_CTX *ctx;
    const BIGNUM *order;
    BIGNUM *u1, *u2, *m, *X;
    EC_POINT *point = NULL;
    const EC_GROUP *group;
    const EC_POINT *pub_key;

    /* check input values */
    if (eckey == NULL || (group = EC_KEY_get0_group(eckey)) == NULL ||
        (pub_key = EC_KEY_get0_public_key(eckey)) == NULL || sig == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, EC_R_MISSING_PARAMETERS);
        return -1;
    }

    if (!EC_KEY_can_sign(eckey)) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, EC_R_CURVE_DOES_NOT_SUPPORT_SIGNING);
        return -1;
    }

    ctx = BN_CTX_new_ex(eckey->libctx);
    if (ctx == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_MALLOC_FAILURE);
        return -1;
    }
    BN_CTX_start(ctx);
    u1 = BN_CTX_get(ctx);
    u2 = BN_CTX_get(ctx);
    m = BN_CTX_get(ctx);
    X = BN_CTX_get(ctx);
    if (X == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_BN_LIB);
        goto err;
    }

    order = EC_GROUP_get0_order(group);
    if (order == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_EC_LIB);
        goto err;
    }

    if (BN_is_zero(sig->r) || BN_is_negative(sig->r) ||
        BN_ucmp(sig->r, order) >= 0 || BN_is_zero(sig->s) ||
        BN_is_negative(sig->s) || BN_ucmp(sig->s, order) >= 0) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, EC_R_BAD_SIGNATURE);
        ret = 0;                /* signature is invalid */
        goto err;
    }
    /* calculate tmp1 = inv(S) mod order */
    if (!ec_group_do_inverse_ord(group, u2, sig->s, ctx)) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_BN_LIB);
        goto err;
    }
    /* digest -> m */
    i = BN_num_bits(order);
    /*
     * Need to truncate digest if it is too long: first truncate whole bytes.
     */
    if (8 * dgst_len > i)
        dgst_len = (i + 7) / 8;
    if (!BN_bin2bn(dgst, dgst_len, m)) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_BN_LIB);
        goto err;
    }
    /* If still too long truncate remaining bits with a shift */
    if ((8 * dgst_len > i) && !BN_rshift(m, m, 8 - (i & 0x7))) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_BN_LIB);
        goto err;
    }
    /* u1 = m * tmp mod order */
    if (!BN_mod_mul(u1, m, u2, order, ctx)) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_BN_LIB);
        goto err;
    }
    /* u2 = r * w mod q */
    if (!BN_mod_mul(u2, sig->r, u2, order, ctx)) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_BN_LIB);
        goto err;
    }

    if ((point = EC_POINT_new(group)) == NULL) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_MALLOC_FAILURE);
        goto err;
    }
    if (!EC_POINT_mul(group, point, u1, pub_key, u2, ctx)) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_EC_LIB);
        goto err;
    }

    if (!EC_POINT_get_affine_coordinates(group, point, X, NULL, ctx)) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_EC_LIB);
        goto err;
    }

    if (!BN_nnmod(u1, X, order, ctx)) {
        ECerr(EC_F_ECDSA_SIMPLE_VERIFY_SIG, ERR_R_BN_LIB);
        goto err;
    }
    /*  if the signature is correct u1 is equal to sig->r */
    ret = (BN_ucmp(u1, sig->r) == 0);
 err:
    BN_CTX_end(ctx);
    BN_CTX_free(ctx);
    EC_POINT_free(point);
    return ret;
}