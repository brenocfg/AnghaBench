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
struct TYPE_5__ {int /*<<< orphan*/ * mont_data; int /*<<< orphan*/  order; int /*<<< orphan*/  cofactor; int /*<<< orphan*/ * generator; } ;
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  TYPE_1__ EC_GROUP ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 scalar_t__ BN_is_odd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_F_EC_GROUP_SET_GENERATOR ; 
 int /*<<< orphan*/  EC_POINT_copy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_POINT_new (TYPE_1__*) ; 
 int /*<<< orphan*/  ECerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR_R_PASSED_NULL_PARAMETER ; 
 int ec_precompute_mont_data (TYPE_1__*) ; 

int EC_GROUP_set_generator(EC_GROUP *group, const EC_POINT *generator,
                           const BIGNUM *order, const BIGNUM *cofactor)
{
    if (generator == NULL) {
        ECerr(EC_F_EC_GROUP_SET_GENERATOR, ERR_R_PASSED_NULL_PARAMETER);
        return 0;
    }

    if (group->generator == NULL) {
        group->generator = EC_POINT_new(group);
        if (group->generator == NULL)
            return 0;
    }
    if (!EC_POINT_copy(group->generator, generator))
        return 0;

    if (order != NULL) {
        if (!BN_copy(group->order, order))
            return 0;
    } else {
        BN_zero(group->order);
    }

    /* The cofactor is an optional field, so it should be able to be NULL. */
    if (cofactor != NULL) {
        if (!BN_copy(group->cofactor, cofactor))
            return 0;
    } else {
        BN_zero(group->cofactor);
    }
    /*
     * Some groups have an order with
     * factors of two, which makes the Montgomery setup fail.
     * |group->mont_data| will be NULL in this case.
     */
    if (BN_is_odd(group->order)) {
        return ec_precompute_mont_data(group);
    }

    BN_MONT_CTX_free(group->mont_data);
    group->mont_data = NULL;
    return 1;
}