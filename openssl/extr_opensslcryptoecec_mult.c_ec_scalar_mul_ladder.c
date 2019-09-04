#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
struct TYPE_32__ {int /*<<< orphan*/ * field; int /*<<< orphan*/  cofactor; int /*<<< orphan*/  order; TYPE_1__ const* generator; } ;
struct TYPE_31__ {int Z_is_one; int /*<<< orphan*/ * Z; int /*<<< orphan*/ * Y; int /*<<< orphan*/ * X; } ;
typedef  TYPE_1__ EC_POINT ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_FLG_CONSTTIME ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_consttime_swap (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int BN_is_bit_set (int /*<<< orphan*/ *,int) ; 
 scalar_t__ BN_is_negative (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_mul (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_nnmod (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int BN_num_bits (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_set_flags (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_SCALAR_MUL_LADDER ; 
 int /*<<< orphan*/  EC_POINT_BN_set_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_POINT_clear_free (TYPE_1__*) ; 
 int /*<<< orphan*/  EC_POINT_copy (TYPE_1__*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  EC_POINT_free (TYPE_1__*) ; 
 scalar_t__ EC_POINT_is_at_infinity (TYPE_2__ const*,TYPE_1__ const*) ; 
 TYPE_1__* EC_POINT_new (TYPE_2__ const*) ; 
 int EC_POINT_set_to_infinity (TYPE_2__ const*,TYPE_1__*) ; 
 int /*<<< orphan*/  EC_R_LADDER_POST_FAILURE ; 
 int /*<<< orphan*/  EC_R_LADDER_PRE_FAILURE ; 
 int /*<<< orphan*/  EC_R_LADDER_STEP_FAILURE ; 
 int /*<<< orphan*/  EC_R_POINT_COORDINATES_BLIND_FAILURE ; 
 int /*<<< orphan*/  EC_R_UNKNOWN_COFACTOR ; 
 int /*<<< orphan*/  EC_R_UNKNOWN_ORDER ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_BN_LIB ; 
 int /*<<< orphan*/  ERR_R_EC_LIB ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int bn_get_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bn_wexpand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ec_point_blind_coordinates (TYPE_2__ const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_point_ladder_post (TYPE_2__ const*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_point_ladder_pre (TYPE_2__ const*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_point_ladder_step (TYPE_2__ const*,TYPE_1__*,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *) ; 

int ec_scalar_mul_ladder(const EC_GROUP *group, EC_POINT *r,
                         const BIGNUM *scalar, const EC_POINT *point,
                         BN_CTX *ctx)
{
    int i, cardinality_bits, group_top, kbit, pbit, Z_is_one;
    EC_POINT *p = NULL;
    EC_POINT *s = NULL;
    BIGNUM *k = NULL;
    BIGNUM *lambda = NULL;
    BIGNUM *cardinality = NULL;
    int ret = 0;

    /* early exit if the input point is the point at infinity */
    if (point != NULL && EC_POINT_is_at_infinity(group, point))
        return EC_POINT_set_to_infinity(group, r);

    if (BN_is_zero(group->order)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, EC_R_UNKNOWN_ORDER);
        return 0;
    }
    if (BN_is_zero(group->cofactor)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, EC_R_UNKNOWN_COFACTOR);
        return 0;
    }

    BN_CTX_start(ctx);

    if (((p = EC_POINT_new(group)) == NULL)
        || ((s = EC_POINT_new(group)) == NULL)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (point == NULL) {
        if (!EC_POINT_copy(p, group->generator)) {
            ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_EC_LIB);
            goto err;
        }
    } else {
        if (!EC_POINT_copy(p, point)) {
            ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_EC_LIB);
            goto err;
        }
    }

    EC_POINT_BN_set_flags(p, BN_FLG_CONSTTIME);
    EC_POINT_BN_set_flags(r, BN_FLG_CONSTTIME);
    EC_POINT_BN_set_flags(s, BN_FLG_CONSTTIME);

    cardinality = BN_CTX_get(ctx);
    lambda = BN_CTX_get(ctx);
    k = BN_CTX_get(ctx);
    if (k == NULL) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (!BN_mul(cardinality, group->order, group->cofactor, ctx)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_BN_LIB);
        goto err;
    }

    /*
     * Group cardinalities are often on a word boundary.
     * So when we pad the scalar, some timing diff might
     * pop if it needs to be expanded due to carries.
     * So expand ahead of time.
     */
    cardinality_bits = BN_num_bits(cardinality);
    group_top = bn_get_top(cardinality);
    if ((bn_wexpand(k, group_top + 2) == NULL)
        || (bn_wexpand(lambda, group_top + 2) == NULL)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_BN_LIB);
        goto err;
    }

    if (!BN_copy(k, scalar)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_BN_LIB);
        goto err;
    }

    BN_set_flags(k, BN_FLG_CONSTTIME);

    if ((BN_num_bits(k) > cardinality_bits) || (BN_is_negative(k))) {
        /*-
         * this is an unusual input, and we don't guarantee
         * constant-timeness
         */
        if (!BN_nnmod(k, k, cardinality, ctx)) {
            ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_BN_LIB);
            goto err;
        }
    }

    if (!BN_add(lambda, k, cardinality)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_BN_LIB);
        goto err;
    }
    BN_set_flags(lambda, BN_FLG_CONSTTIME);
    if (!BN_add(k, lambda, cardinality)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_BN_LIB);
        goto err;
    }
    /*
     * lambda := scalar + cardinality
     * k := scalar + 2*cardinality
     */
    kbit = BN_is_bit_set(lambda, cardinality_bits);
    BN_consttime_swap(kbit, k, lambda, group_top + 2);

    group_top = bn_get_top(group->field);
    if ((bn_wexpand(s->X, group_top) == NULL)
        || (bn_wexpand(s->Y, group_top) == NULL)
        || (bn_wexpand(s->Z, group_top) == NULL)
        || (bn_wexpand(r->X, group_top) == NULL)
        || (bn_wexpand(r->Y, group_top) == NULL)
        || (bn_wexpand(r->Z, group_top) == NULL)
        || (bn_wexpand(p->X, group_top) == NULL)
        || (bn_wexpand(p->Y, group_top) == NULL)
        || (bn_wexpand(p->Z, group_top) == NULL)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, ERR_R_BN_LIB);
        goto err;
    }

    /*-
     * Apply coordinate blinding for EC_POINT.
     *
     * The underlying EC_METHOD can optionally implement this function:
     * ec_point_blind_coordinates() returns 0 in case of errors or 1 on
     * success or if coordinate blinding is not implemented for this
     * group.
     */
    if (!ec_point_blind_coordinates(group, p, ctx)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, EC_R_POINT_COORDINATES_BLIND_FAILURE);
        goto err;
    }

    /* Initialize the Montgomery ladder */
    if (!ec_point_ladder_pre(group, r, s, p, ctx)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, EC_R_LADDER_PRE_FAILURE);
        goto err;
    }

    /* top bit is a 1, in a fixed pos */
    pbit = 1;

#define EC_POINT_CSWAP(c, a, b, w, t) do {         \
        BN_consttime_swap(c, (a)->X, (b)->X, w);   \
        BN_consttime_swap(c, (a)->Y, (b)->Y, w);   \
        BN_consttime_swap(c, (a)->Z, (b)->Z, w);   \
        t = ((a)->Z_is_one ^ (b)->Z_is_one) & (c); \
        (a)->Z_is_one ^= (t);                      \
        (b)->Z_is_one ^= (t);                      \
} while(0)

    /*-
     * The ladder step, with branches, is
     *
     * k[i] == 0: S = add(R, S), R = dbl(R)
     * k[i] == 1: R = add(S, R), S = dbl(S)
     *
     * Swapping R, S conditionally on k[i] leaves you with state
     *
     * k[i] == 0: T, U = R, S
     * k[i] == 1: T, U = S, R
     *
     * Then perform the ECC ops.
     *
     * U = add(T, U)
     * T = dbl(T)
     *
     * Which leaves you with state
     *
     * k[i] == 0: U = add(R, S), T = dbl(R)
     * k[i] == 1: U = add(S, R), T = dbl(S)
     *
     * Swapping T, U conditionally on k[i] leaves you with state
     *
     * k[i] == 0: R, S = T, U
     * k[i] == 1: R, S = U, T
     *
     * Which leaves you with state
     *
     * k[i] == 0: S = add(R, S), R = dbl(R)
     * k[i] == 1: R = add(S, R), S = dbl(S)
     *
     * So we get the same logic, but instead of a branch it's a
     * conditional swap, followed by ECC ops, then another conditional swap.
     *
     * Optimization: The end of iteration i and start of i-1 looks like
     *
     * ...
     * CSWAP(k[i], R, S)
     * ECC
     * CSWAP(k[i], R, S)
     * (next iteration)
     * CSWAP(k[i-1], R, S)
     * ECC
     * CSWAP(k[i-1], R, S)
     * ...
     *
     * So instead of two contiguous swaps, you can merge the condition
     * bits and do a single swap.
     *
     * k[i]   k[i-1]    Outcome
     * 0      0         No Swap
     * 0      1         Swap
     * 1      0         Swap
     * 1      1         No Swap
     *
     * This is XOR. pbit tracks the previous bit of k.
     */

    for (i = cardinality_bits - 1; i >= 0; i--) {
        kbit = BN_is_bit_set(k, i) ^ pbit;
        EC_POINT_CSWAP(kbit, r, s, group_top, Z_is_one);

        /* Perform a single step of the Montgomery ladder */
        if (!ec_point_ladder_step(group, r, s, p, ctx)) {
            ECerr(EC_F_EC_SCALAR_MUL_LADDER, EC_R_LADDER_STEP_FAILURE);
            goto err;
        }
        /*
         * pbit logic merges this cswap with that of the
         * next iteration
         */
        pbit ^= kbit;
    }
    /* one final cswap to move the right value into r */
    EC_POINT_CSWAP(pbit, r, s, group_top, Z_is_one);
#undef EC_POINT_CSWAP

    /* Finalize ladder (and recover full point coordinates) */
    if (!ec_point_ladder_post(group, r, s, p, ctx)) {
        ECerr(EC_F_EC_SCALAR_MUL_LADDER, EC_R_LADDER_POST_FAILURE);
        goto err;
    }

    ret = 1;

 err:
    EC_POINT_free(p);
    EC_POINT_clear_free(s);
    BN_CTX_end(ctx);

    return ret;
}