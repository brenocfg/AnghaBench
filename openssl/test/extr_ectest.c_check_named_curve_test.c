#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  invalid_seed ;
struct TYPE_2__ {int nid; } ;
typedef  int /*<<< orphan*/  const EC_POINT ;
typedef  int /*<<< orphan*/  const EC_GROUP ;
typedef  int /*<<< orphan*/  const BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_CTX_new () ; 
 scalar_t__ BN_add_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  const* BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const* BN_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_get0_nist_prime_192 () ; 
 int /*<<< orphan*/  BN_get0_nist_prime_256 () ; 
 scalar_t__ BN_lshift1 (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_new () ; 
 scalar_t__ BN_ucmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_check_named_curve (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EC_GROUP_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_generator (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_order (int /*<<< orphan*/  const*) ; 
 scalar_t__ EC_GROUP_get_cofactor (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_GROUP_get_curve (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ EC_GROUP_get_seed_len (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_method_of (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_new_by_curve_name (int) ; 
 scalar_t__ EC_GROUP_set_curve (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_set_curve_name (int /*<<< orphan*/  const*,int) ; 
 scalar_t__ EC_GROUP_set_generator (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_set_seed (int /*<<< orphan*/  const*,unsigned char const*,size_t) ; 
 int EC_METHOD_get_field_type (int /*<<< orphan*/ ) ; 
 scalar_t__ EC_POINT_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EC_POINT_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/ * EC_curve_nid2nist (int) ; 
 int /*<<< orphan*/  ERR_pop_to_mark () ; 
 int /*<<< orphan*/  ERR_set_mark () ; 
 int NID_X9_62_characteristic_two_field ; 
 int NID_undef ; 
 int /*<<< orphan*/  TEST_false (scalar_t__) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (scalar_t__) ; 
 TYPE_1__* curves ; 

__attribute__((used)) static int check_named_curve_test(int id)
{
    int ret = 0, nid, field_nid, has_seed;
    EC_GROUP *group = NULL, *gtest = NULL;
    const EC_POINT *group_gen = NULL;
    EC_POINT *other_gen = NULL;
    BIGNUM *group_p = NULL, *group_a = NULL, *group_b = NULL;
    BIGNUM *other_p = NULL, *other_a = NULL, *other_b = NULL;
    BIGNUM *group_cofactor = NULL, *other_cofactor = NULL;
    BIGNUM *other_order = NULL;
    const BIGNUM *group_order = NULL;
    BN_CTX *bn_ctx = NULL;
    static const unsigned char invalid_seed[] = "THIS IS NOT A VALID SEED";
    static size_t invalid_seed_len = sizeof(invalid_seed);

    /* Do some setup */
    nid = curves[id].nid;
    if (!TEST_ptr(bn_ctx = BN_CTX_new())
        || !TEST_ptr(group = EC_GROUP_new_by_curve_name(nid))
        || !TEST_ptr(gtest = EC_GROUP_dup(group))
        || !TEST_ptr(group_p = BN_new())
        || !TEST_ptr(group_a = BN_new())
        || !TEST_ptr(group_b = BN_new())
        || !TEST_ptr(group_cofactor = BN_new())
        || !TEST_ptr(group_gen = EC_GROUP_get0_generator(group))
        || !TEST_ptr(group_order = EC_GROUP_get0_order(group))
        || !TEST_true(EC_GROUP_get_cofactor(group, group_cofactor, NULL))
        || !TEST_true(EC_GROUP_get_curve(group, group_p, group_a, group_b, NULL))
        || !TEST_ptr(other_gen = EC_POINT_dup(group_gen, group))
        || !TEST_true(EC_POINT_add(group, other_gen, group_gen, group_gen, NULL))
        || !TEST_ptr(other_order = BN_dup(group_order))
        || !TEST_true(BN_add_word(other_order, 1))
        || !TEST_ptr(other_a = BN_dup(group_a))
        || !TEST_true(BN_add_word(other_a, 1))
        || !TEST_ptr(other_b = BN_dup(group_b))
        || !TEST_true(BN_add_word(other_b, 1))
        || !TEST_ptr(other_cofactor = BN_dup(group_cofactor))
        || !TEST_true(BN_add_word(other_cofactor, 1)))
        goto err;

    /* Determine if the built-in curve has a seed field set */
    has_seed = (EC_GROUP_get_seed_len(group) > 0);
    field_nid = EC_METHOD_get_field_type(EC_GROUP_method_of(group));
    if (field_nid == NID_X9_62_characteristic_two_field) {
        if (!TEST_ptr(other_p = BN_dup(group_p))
            || !TEST_true(BN_lshift1(other_p, other_p)))
            goto err;
    } else {
        if (!TEST_ptr(other_p = BN_dup(group_p)))
            goto err;
        /*
         * Just choosing any arbitrary prime does not work..
         * Setting p via ec_GFp_nist_group_set_curve() needs the prime to be a
         * nist prime. So only select one of these as an alternate prime.
         */
        if (!TEST_ptr(BN_copy(other_p,
                              BN_ucmp(BN_get0_nist_prime_192(), other_p) == 0 ?
                                      BN_get0_nist_prime_256() :
                                      BN_get0_nist_prime_192())))
            goto err;
    }

    /* Passes because this is a valid curve */
    if (!TEST_int_eq(EC_GROUP_check_named_curve(group, 0, NULL), nid)
        /* Only NIST curves pass */
        || !TEST_int_eq(EC_GROUP_check_named_curve(group, 1, NULL),
                        EC_curve_nid2nist(nid) != NULL ? nid : NID_undef))
        goto err;

    /* Fail if the curve name doesn't match the parameters */
    EC_GROUP_set_curve_name(group, nid + 1);
    ERR_set_mark();
    if (!TEST_int_le(EC_GROUP_check_named_curve(group, 0, NULL), 0))
        goto err;
    ERR_pop_to_mark();

    /* Restore curve name and ensure it's passing */
    EC_GROUP_set_curve_name(group, nid);
    if (!TEST_int_eq(EC_GROUP_check_named_curve(group, 0, NULL), nid))
        goto err;

    if (!TEST_int_eq(EC_GROUP_set_seed(group, invalid_seed, invalid_seed_len),
                     invalid_seed_len))
        goto err;

    if (has_seed) {
        /*
         * If the built-in curve has a seed and we set the seed to another value
         * then it will fail the check.
         */
        if (!TEST_int_eq(EC_GROUP_check_named_curve(group, 0, NULL), 0))
            goto err;
    } else {
        /*
         * If the built-in curve does not have a seed then setting the seed will
         * pass the check (as the seed is optional).
         */
        if (!TEST_int_eq(EC_GROUP_check_named_curve(group, 0, NULL), nid))
            goto err;
    }
    /* Pass if the seed is unknown (as it is optional) */
    if (!TEST_int_eq(EC_GROUP_set_seed(group, NULL, 0), 1)
        || !TEST_int_eq(EC_GROUP_check_named_curve(group, 0, NULL), nid))
        goto err;

    /* Check that a duped group passes */
    if (!TEST_int_eq(EC_GROUP_check_named_curve(gtest, 0, NULL), nid))
        goto err;

    /* check that changing any generator parameter fails */
    if (!TEST_true(EC_GROUP_set_generator(gtest, other_gen, group_order,
                                          group_cofactor))
        || !TEST_int_eq(EC_GROUP_check_named_curve(gtest, 0, NULL), 0)
        || !TEST_true(EC_GROUP_set_generator(gtest, group_gen, other_order,
                                             group_cofactor))
        || !TEST_int_eq(EC_GROUP_check_named_curve(gtest, 0, NULL), 0)
        /* The order is not an optional field, so this should fail */
        || !TEST_false(EC_GROUP_set_generator(gtest, group_gen, NULL,
                                              group_cofactor))
        || !TEST_true(EC_GROUP_set_generator(gtest, group_gen, group_order,
                                             other_cofactor))
        || !TEST_int_eq(EC_GROUP_check_named_curve(gtest, 0, NULL), 0)
        /* Check that if the cofactor is not set then it still passes */
        || !TEST_true(EC_GROUP_set_generator(gtest, group_gen, group_order,
                                             NULL))
        || !TEST_int_eq(EC_GROUP_check_named_curve(gtest, 0, NULL), nid)
        /* check that restoring the generator passes */
        || !TEST_true(EC_GROUP_set_generator(gtest, group_gen, group_order,
                                             group_cofactor))
        || !TEST_int_eq(EC_GROUP_check_named_curve(gtest, 0, NULL), nid))
        goto err;

    /*
     * check that changing any curve parameter fails
     *
     * Setting arbitrary p, a or b might fail for some EC_GROUPs
     * depending on the internal EC_METHOD implementation, hence run
     * these tests conditionally to the success of EC_GROUP_set_curve().
     */
    ERR_set_mark();
    if (EC_GROUP_set_curve(gtest, other_p, group_a, group_b, NULL)) {
        if (!TEST_int_le(EC_GROUP_check_named_curve(gtest, 0, NULL), 0))
            goto err;
    } else {
        /* clear the error stack if EC_GROUP_set_curve() failed */
        ERR_pop_to_mark();
        ERR_set_mark();
    }
    if (EC_GROUP_set_curve(gtest, group_p, other_a, group_b, NULL)) {
        if (!TEST_int_le(EC_GROUP_check_named_curve(gtest, 0, NULL), 0))
            goto err;
    } else {
        /* clear the error stack if EC_GROUP_set_curve() failed */
        ERR_pop_to_mark();
        ERR_set_mark();
    }
    if (EC_GROUP_set_curve(gtest, group_p, group_a, other_b, NULL)) {
        if (!TEST_int_le(EC_GROUP_check_named_curve(gtest, 0, NULL), 0))
            goto err;
    } else {
        /* clear the error stack if EC_GROUP_set_curve() failed */
        ERR_pop_to_mark();
        ERR_set_mark();
    }
    ERR_pop_to_mark();

    /* Check that restoring the curve parameters passes */
    if (!TEST_true(EC_GROUP_set_curve(gtest, group_p, group_a, group_b, NULL))
        || !TEST_int_eq(EC_GROUP_check_named_curve(gtest, 0, NULL), nid))
        goto err;

    ret = 1;
err:
    BN_free(group_p);
    BN_free(other_p);
    BN_free(group_a);
    BN_free(other_a);
    BN_free(group_b);
    BN_free(other_b);
    BN_free(group_cofactor);
    BN_free(other_cofactor);
    BN_free(other_order);
    EC_POINT_free(other_gen);
    EC_GROUP_free(gtest);
    EC_GROUP_free(group);
    BN_CTX_free(bn_ctx);
    return ret;
}