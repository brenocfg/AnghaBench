#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_1__* meth; } ;
struct TYPE_13__ {int flags; int /*<<< orphan*/  (* group_get_curve ) (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/ *) ; 
 scalar_t__ BN_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_is_zero (int /*<<< orphan*/  const*) ; 
 int EC_FLAGS_CUSTOM_CURVE ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_cofactor (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_GROUP_get0_generator (TYPE_2__ const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_order (TYPE_2__ const*) ; 
 scalar_t__ EC_GROUP_get_curve_name (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_GROUP_method_of (TYPE_2__ const*) ; 
 scalar_t__ EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 scalar_t__ EC_POINT_cmp (TYPE_2__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__ const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

int EC_GROUP_cmp(const EC_GROUP *a, const EC_GROUP *b, BN_CTX *ctx)
{
    int r = 0;
    BIGNUM *a1, *a2, *a3, *b1, *b2, *b3;
#ifndef FIPS_MODE
    BN_CTX *ctx_new = NULL;

    if (ctx == NULL)
        ctx_new = ctx = BN_CTX_new();
#endif
    if (ctx == NULL)
        return -1;

    /* compare the field types */
    if (EC_METHOD_get_field_type(EC_GROUP_method_of(a)) !=
        EC_METHOD_get_field_type(EC_GROUP_method_of(b)))
        return 1;
    /* compare the curve name (if present in both) */
    if (EC_GROUP_get_curve_name(a) && EC_GROUP_get_curve_name(b) &&
        EC_GROUP_get_curve_name(a) != EC_GROUP_get_curve_name(b))
        return 1;
    if (a->meth->flags & EC_FLAGS_CUSTOM_CURVE)
        return 0;

    BN_CTX_start(ctx);
    a1 = BN_CTX_get(ctx);
    a2 = BN_CTX_get(ctx);
    a3 = BN_CTX_get(ctx);
    b1 = BN_CTX_get(ctx);
    b2 = BN_CTX_get(ctx);
    b3 = BN_CTX_get(ctx);
    if (b3 == NULL) {
        BN_CTX_end(ctx);
#ifndef FIPS_MODE
        BN_CTX_free(ctx_new);
#endif
        return -1;
    }

    /*
     * XXX This approach assumes that the external representation of curves
     * over the same field type is the same.
     */
    if (!a->meth->group_get_curve(a, a1, a2, a3, ctx) ||
        !b->meth->group_get_curve(b, b1, b2, b3, ctx))
        r = 1;

    /* return 1 if the curve parameters are different */
    if (r || BN_cmp(a1, b1) != 0 || BN_cmp(a2, b2) != 0 || BN_cmp(a3, b3) != 0)
        r = 1;

    /* XXX EC_POINT_cmp() assumes that the methods are equal */
    /* return 1 if the generators are different */
    if (r || EC_POINT_cmp(a, EC_GROUP_get0_generator(a),
                          EC_GROUP_get0_generator(b), ctx) != 0)
        r = 1;

    if (!r) {
        const BIGNUM *ao, *bo, *ac, *bc;
        /* compare the orders */
        ao = EC_GROUP_get0_order(a);
        bo = EC_GROUP_get0_order(b);
        if (ao == NULL || bo == NULL) {
            /* return an error if either order is NULL */
            r = -1;
            goto end;
        }
        if (BN_cmp(ao, bo) != 0) {
            /* return 1 if orders are different */
            r = 1;
            goto end;
        }
        /*
         * It gets here if the curve parameters and generator matched.
         * Now check the optional cofactors (if both are present).
         */
        ac = EC_GROUP_get0_cofactor(a);
        bc = EC_GROUP_get0_cofactor(b);
        /* Returns 1 (mismatch) if both cofactors are specified and different */
        if (!BN_is_zero(ac) && !BN_is_zero(bc) && BN_cmp(ac, bc) != 0)
            r = 1;
        /* Returns 0 if the parameters matched */
    }
end:
    BN_CTX_end(ctx);
#ifndef FIPS_MODE
    BN_CTX_free(ctx_new);
#endif
    return r;
}