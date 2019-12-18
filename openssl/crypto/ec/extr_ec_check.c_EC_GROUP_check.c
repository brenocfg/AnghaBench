#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * generator; TYPE_1__* meth; } ;
struct TYPE_11__ {int flags; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_2__ EC_GROUP ;
typedef  int /*<<< orphan*/  BN_CTX ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 scalar_t__ BN_is_zero (int /*<<< orphan*/  const*) ; 
 int EC_FLAGS_CUSTOM_CURVE ; 
 int /*<<< orphan*/  EC_F_EC_GROUP_CHECK ; 
 int /*<<< orphan*/  EC_GROUP_check_discriminant (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_GROUP_check_named_curve (TYPE_2__ const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_get0_order (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_is_at_infinity (TYPE_2__ const*,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_POINT_is_on_curve (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_mul (TYPE_2__ const*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_2__ const*) ; 
 int /*<<< orphan*/  EC_R_DISCRIMINANT_IS_ZERO ; 
 int /*<<< orphan*/  EC_R_INVALID_GROUP_ORDER ; 
 int /*<<< orphan*/  EC_R_POINT_IS_NOT_ON_CURVE ; 
 int /*<<< orphan*/  EC_R_UNDEFINED_GENERATOR ; 
 int /*<<< orphan*/  EC_R_UNDEFINED_ORDER ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_MALLOC_FAILURE ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 

int EC_GROUP_check(const EC_GROUP *group, BN_CTX *ctx)
{
#ifdef FIPS_MODE
    /*
    * ECC domain parameter validation.
    * See SP800-56A R3 5.5.2 "Assurances of Domain-Parameter Validity" Part 1b.
    */
    return EC_GROUP_check_named_curve(group, 1, ctx) >= 0 ? 1 : 0;
#else
    int ret = 0;
    const BIGNUM *order;
    BN_CTX *new_ctx = NULL;
    EC_POINT *point = NULL;

    if (group == NULL || group->meth == NULL) {
        ECerr(EC_F_EC_GROUP_CHECK, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    /* Custom curves assumed to be correct */
    if ((group->meth->flags & EC_FLAGS_CUSTOM_CURVE) != 0)
        return 1;

    if (ctx == NULL) {
        ctx = new_ctx = BN_CTX_new();
        if (ctx == NULL) {
            ECerr(EC_F_EC_GROUP_CHECK, ERR_R_MALLOC_FAILURE);
            goto err;
        }
    }

    /* check the discriminant */
    if (!EC_GROUP_check_discriminant(group, ctx)) {
        ECerr(EC_F_EC_GROUP_CHECK, EC_R_DISCRIMINANT_IS_ZERO);
        goto err;
    }

    /* check the generator */
    if (group->generator == NULL) {
        ECerr(EC_F_EC_GROUP_CHECK, EC_R_UNDEFINED_GENERATOR);
        goto err;
    }
    if (EC_POINT_is_on_curve(group, group->generator, ctx) <= 0) {
        ECerr(EC_F_EC_GROUP_CHECK, EC_R_POINT_IS_NOT_ON_CURVE);
        goto err;
    }

    /* check the order of the generator */
    if ((point = EC_POINT_new(group)) == NULL)
        goto err;
    order = EC_GROUP_get0_order(group);
    if (order == NULL)
        goto err;
    if (BN_is_zero(order)) {
        ECerr(EC_F_EC_GROUP_CHECK, EC_R_UNDEFINED_ORDER);
        goto err;
    }

    if (!EC_POINT_mul(group, point, order, NULL, NULL, ctx))
        goto err;
    if (!EC_POINT_is_at_infinity(group, point)) {
        ECerr(EC_F_EC_GROUP_CHECK, EC_R_INVALID_GROUP_ORDER);
        goto err;
    }

    ret = 1;

 err:
    BN_CTX_free(new_ctx);
    EC_POINT_free(point);
    return ret;
#endif /* FIPS_MODE */
}