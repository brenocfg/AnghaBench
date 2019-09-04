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
struct TYPE_5__ {size_t blocksize; size_t numblocks; size_t w; size_t num; int /*<<< orphan*/  const** points; int /*<<< orphan*/ * group; } ;
typedef  TYPE_1__ EC_PRE_COMP ;
typedef  int /*<<< orphan*/  const EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 size_t BN_num_bits (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_F_EC_WNAF_PRECOMPUTE_MULT ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_generator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_get0_order (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_add (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_dbl (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_POINT_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINTs_make_affine (int /*<<< orphan*/ *,size_t,int /*<<< orphan*/  const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_R_UNDEFINED_GENERATOR ; 
 int /*<<< orphan*/  EC_R_UNKNOWN_ORDER ; 
 int /*<<< orphan*/  EC_ec_pre_comp_free (TYPE_1__*) ; 
 int /*<<< orphan*/  EC_pre_comp_free (int /*<<< orphan*/ *) ; 
 size_t EC_window_bits_for_scalar_size (size_t) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  OPENSSL_free (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  const** OPENSSL_malloc (int) ; 
 int /*<<< orphan*/  SETPRECOMP (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ec ; 
 TYPE_1__* ec_pre_comp_new (int /*<<< orphan*/ *) ; 

int ec_wNAF_precompute_mult(EC_GROUP *group, BN_CTX *ctx)
{
    const EC_POINT *generator;
    EC_POINT *tmp_point = NULL, *base = NULL, **var;
    BN_CTX *new_ctx = NULL;
    const BIGNUM *order;
    size_t i, bits, w, pre_points_per_block, blocksize, numblocks, num;
    EC_POINT **points = NULL;
    EC_PRE_COMP *pre_comp;
    int ret = 0;

    /* if there is an old EC_PRE_COMP object, throw it away */
    EC_pre_comp_free(group);
    if ((pre_comp = ec_pre_comp_new(group)) == NULL)
        return 0;

    generator = EC_GROUP_get0_generator(group);
    if (generator == NULL) {
        ECerr(EC_F_EC_WNAF_PRECOMPUTE_MULT, EC_R_UNDEFINED_GENERATOR);
        goto err;
    }

    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == NULL)
            goto err;
    }

    BN_CTX_start(ctx);

    order = EC_GROUP_get0_order(group);
    if (order == NULL)
        goto err;
    if (BN_is_zero(order)) {
        ECerr(EC_F_EC_WNAF_PRECOMPUTE_MULT, EC_R_UNKNOWN_ORDER);
        goto err;
    }

    bits = BN_num_bits(order);
    /*
     * The following parameters mean we precompute (approximately) one point
     * per bit. TBD: The combination 8, 4 is perfect for 160 bits; for other
     * bit lengths, other parameter combinations might provide better
     * efficiency.
     */
    blocksize = 8;
    w = 4;
    if (EC_window_bits_for_scalar_size(bits) > w) {
        /* let's not make the window too small ... */
        w = EC_window_bits_for_scalar_size(bits);
    }

    numblocks = (bits + blocksize - 1) / blocksize; /* max. number of blocks
                                                     * to use for wNAF
                                                     * splitting */

    pre_points_per_block = (size_t)1 << (w - 1);
    num = pre_points_per_block * numblocks; /* number of points to compute
                                             * and store */

    points = OPENSSL_malloc(sizeof(*points) * (num + 1));
    if (points == NULL) {
        ECerr(EC_F_EC_WNAF_PRECOMPUTE_MULT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    var = points;
    var[num] = NULL;            /* pivot */
    for (i = 0; i < num; i++) {
        if ((var[i] = EC_POINT_new(group)) == NULL) {
            ECerr(EC_F_EC_WNAF_PRECOMPUTE_MULT, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }

    if ((tmp_point = EC_POINT_new(group)) == NULL
        || (base = EC_POINT_new(group)) == NULL) {
        ECerr(EC_F_EC_WNAF_PRECOMPUTE_MULT, ERR_R_MALLOC_FAILURE);
        goto err;
    }

    if (!EC_POINT_copy(base, generator))
        goto err;

    /* do the precomputation */
    for (i = 0; i < numblocks; i++) {
        size_t j;

        if (!EC_POINT_dbl(group, tmp_point, base, ctx))
            goto err;

        if (!EC_POINT_copy(*var++, base))
            goto err;

        for (j = 1; j < pre_points_per_block; j++, var++) {
            /*
             * calculate odd multiples of the current base point
             */
            if (!EC_POINT_add(group, *var, tmp_point, *(var - 1), ctx))
                goto err;
        }

        if (i < numblocks - 1) {
            /*
             * get the next base (multiply current one by 2^blocksize)
             */
            size_t k;

            if (blocksize <= 2) {
                ECerr(EC_F_EC_WNAF_PRECOMPUTE_MULT, ERR_R_INTERNAL_ERROR);
                goto err;
            }

            if (!EC_POINT_dbl(group, base, tmp_point, ctx))
                goto err;
            for (k = 2; k < blocksize; k++) {
                if (!EC_POINT_dbl(group, base, base, ctx))
                    goto err;
            }
        }
    }

    if (!EC_POINTs_make_affine(group, num, points, ctx))
        goto err;

    pre_comp->group = group;
    pre_comp->blocksize = blocksize;
    pre_comp->numblocks = numblocks;
    pre_comp->w = w;
    pre_comp->points = points;
    points = NULL;
    pre_comp->num = num;
    SETPRECOMP(group, ec, pre_comp);
    pre_comp = NULL;
    ret = 1;

 err:
    BN_CTX_end(ctx);
    BN_CTX_free(new_ctx);
    EC_ec_pre_comp_free(pre_comp);
    if (points) {
        EC_POINT **p;

        for (p = points; *p != NULL; p++)
            EC_POINT_free(*p);
        OPENSSL_free(points);
    }
    EC_POINT_free(tmp_point);
    EC_POINT_free(base);
    return ret;
}