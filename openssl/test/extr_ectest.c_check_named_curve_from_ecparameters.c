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
typedef  int /*<<< orphan*/  const ECPARAMETERS ;
typedef  int /*<<< orphan*/  const BN_CTX ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_end (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_CTX_get (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_CTX_new () ; 
 int /*<<< orphan*/  BN_CTX_start (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_add_word (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  ECPARAMETERS_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_dup (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_generator (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_order (int /*<<< orphan*/  const*) ; 
 int EC_GROUP_get_asn1_flag (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_get_cofactor (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int EC_GROUP_get_curve_name (int /*<<< orphan*/  const*) ; 
 void* EC_GROUP_get_ecparameters (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EC_GROUP_new_by_curve_name (int) ; 
 void* EC_GROUP_new_from_ecparameters (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_GROUP_set_generator (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int EC_GROUP_set_seed (int /*<<< orphan*/  const*,unsigned char const*,size_t) ; 
 int /*<<< orphan*/  EC_POINT_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  const* EC_POINT_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_POINT_new (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_set_affine_coordinates (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int NID_undef ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int OPENSSL_EC_EXPLICIT_CURVE ; 
 int OSSL_NELEM (int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  TEST_false (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_eq (int,int) ; 
 int /*<<< orphan*/  TEST_int_ne (int,int) ; 
 int /*<<< orphan*/  TEST_note (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  are_ec_nids_compatible (int,int) ; 
 TYPE_1__* curves ; 

__attribute__((used)) static int check_named_curve_from_ecparameters(int id)
{
    int ret = 0, nid, tnid;
    EC_GROUP *group = NULL, *tgroup = NULL, *tmpg = NULL;
    const EC_POINT *group_gen = NULL;
    EC_POINT *other_gen = NULL;
    BIGNUM *group_cofactor = NULL, *other_cofactor = NULL;
    BIGNUM *other_gen_x = NULL, *other_gen_y = NULL;
    const BIGNUM *group_order = NULL;
    BIGNUM *other_order = NULL;
    BN_CTX *bn_ctx = NULL;
    static const unsigned char invalid_seed[] = "THIS IS NOT A VALID SEED";
    static size_t invalid_seed_len = sizeof(invalid_seed);
    ECPARAMETERS *params = NULL, *other_params = NULL;
    EC_GROUP *g_ary[8] = {NULL};
    EC_GROUP **g_next = &g_ary[0];
    ECPARAMETERS *p_ary[8] = {NULL};
    ECPARAMETERS **p_next = &p_ary[0];

    /* Do some setup */
    nid = curves[id].nid;
    TEST_note("Curve %s", OBJ_nid2sn(nid));
    if (!TEST_ptr(bn_ctx = BN_CTX_new()))
        return ret;
    BN_CTX_start(bn_ctx);

    if (/* Allocations */
        !TEST_ptr(group_cofactor = BN_CTX_get(bn_ctx))
        || !TEST_ptr(other_gen_x = BN_CTX_get(bn_ctx))
        || !TEST_ptr(other_gen_y = BN_CTX_get(bn_ctx))
        || !TEST_ptr(other_order = BN_CTX_get(bn_ctx))
        || !TEST_ptr(other_cofactor = BN_CTX_get(bn_ctx))
        /* Generate reference group and params */
        || !TEST_ptr(group = EC_GROUP_new_by_curve_name(nid))
        || !TEST_ptr(params = EC_GROUP_get_ecparameters(group, NULL))
        || !TEST_ptr(group_gen = EC_GROUP_get0_generator(group))
        || !TEST_ptr(group_order = EC_GROUP_get0_order(group))
        || !TEST_true(EC_GROUP_get_cofactor(group, group_cofactor, NULL))
        /* compute `other_*` values */
        || !TEST_ptr(tmpg = EC_GROUP_dup(group))
        || !TEST_ptr(other_gen = EC_POINT_dup(group_gen, group))
        || !TEST_true(EC_POINT_add(group, other_gen, group_gen, group_gen, NULL))
        || !TEST_true(EC_POINT_get_affine_coordinates(group, other_gen,
                      other_gen_x, other_gen_y, bn_ctx))
        || !TEST_true(BN_copy(other_order, group_order))
        || !TEST_true(BN_add_word(other_order, 1))
        || !TEST_true(BN_copy(other_cofactor, group_cofactor))
        || !TEST_true(BN_add_word(other_cofactor, 1)))
        goto err;

    EC_POINT_free(other_gen);
    other_gen = NULL;

    if (!TEST_ptr(other_gen = EC_POINT_new(tmpg))
        || !TEST_true(EC_POINT_set_affine_coordinates(tmpg, other_gen,
                                                      other_gen_x, other_gen_y,
                                                      bn_ctx)))
        goto err;

    /*
     * ###########################
     * # Actual tests start here #
     * ###########################
     */

    /*
     * Creating a group from built-in explicit parameters returns a
     * "named" EC_GROUP
     */
    if (!TEST_ptr(tgroup = *g_next++ = EC_GROUP_new_from_ecparameters(params))
        || !TEST_int_ne((tnid = EC_GROUP_get_curve_name(tgroup)), NID_undef))
        goto err;
    /*
     * We cannot always guarantee the names match, as the built-in table
     * contains aliases for the same curve with different names.
     */
    if (!TEST_true(are_ec_nids_compatible(nid, tnid))) {
        TEST_info("nid = %s, tnid = %s", OBJ_nid2sn(nid), OBJ_nid2sn(tnid));
        goto err;
    }
    /* Ensure that the OPENSSL_EC_EXPLICIT_CURVE ASN1 flag is set. */
    if (!TEST_int_eq(EC_GROUP_get_asn1_flag(tgroup), OPENSSL_EC_EXPLICIT_CURVE))
        goto err;

    /*
     * An invalid seed in the parameters should be ignored: expect a "named"
     * group.
     */
    if (!TEST_int_eq(EC_GROUP_set_seed(tmpg, invalid_seed, invalid_seed_len),
                     invalid_seed_len)
            || !TEST_ptr(other_params = *p_next++ =
                         EC_GROUP_get_ecparameters(tmpg, NULL))
            || !TEST_ptr(tgroup = *g_next++ =
                          EC_GROUP_new_from_ecparameters(other_params))
            || !TEST_int_ne((tnid = EC_GROUP_get_curve_name(tgroup)), NID_undef)
            || !TEST_true(are_ec_nids_compatible(nid, tnid))
            || !TEST_int_eq(EC_GROUP_get_asn1_flag(tgroup),
                            OPENSSL_EC_EXPLICIT_CURVE)) {
        TEST_info("nid = %s, tnid = %s", OBJ_nid2sn(nid), OBJ_nid2sn(tnid));
        goto err;
    }

    /*
     * A null seed in the parameters should be ignored, as it is optional:
     * expect a "named" group.
     */
    if (!TEST_int_eq(EC_GROUP_set_seed(tmpg, NULL, 0), 1)
            || !TEST_ptr(other_params = *p_next++ =
                         EC_GROUP_get_ecparameters(tmpg, NULL))
            || !TEST_ptr(tgroup = *g_next++ =
                          EC_GROUP_new_from_ecparameters(other_params))
            || !TEST_int_ne((tnid = EC_GROUP_get_curve_name(tgroup)), NID_undef)
            || !TEST_true(are_ec_nids_compatible(nid, tnid))
            || !TEST_int_eq(EC_GROUP_get_asn1_flag(tgroup),
                            OPENSSL_EC_EXPLICIT_CURVE)) {
        TEST_info("nid = %s, tnid = %s", OBJ_nid2sn(nid), OBJ_nid2sn(tnid));
        goto err;
    }

    /*
     * Check that changing any of the generator parameters does not yield a
     * match with the built-in curves
     */
    if (/* Other gen, same group order & cofactor */
        !TEST_true(EC_GROUP_set_generator(tmpg, other_gen, group_order,
                                          group_cofactor))
        || !TEST_ptr(other_params = *p_next++ =
                     EC_GROUP_get_ecparameters(tmpg, NULL))
        || !TEST_ptr(tgroup = *g_next++ =
                      EC_GROUP_new_from_ecparameters(other_params))
        || !TEST_int_eq((tnid = EC_GROUP_get_curve_name(tgroup)), NID_undef)
        /* Same gen & cofactor, different order */
        || !TEST_true(EC_GROUP_set_generator(tmpg, group_gen, other_order,
                                             group_cofactor))
        || !TEST_ptr(other_params = *p_next++ =
                     EC_GROUP_get_ecparameters(tmpg, NULL))
        || !TEST_ptr(tgroup = *g_next++ =
                      EC_GROUP_new_from_ecparameters(other_params))
        || !TEST_int_eq((tnid = EC_GROUP_get_curve_name(tgroup)), NID_undef)
        /* The order is not an optional field, so this should fail */
        || !TEST_false(EC_GROUP_set_generator(tmpg, group_gen, NULL,
                                              group_cofactor))
        /* Check that a wrong cofactor is ignored, and we still match */
        || !TEST_true(EC_GROUP_set_generator(tmpg, group_gen, group_order,
                                             other_cofactor))
        || !TEST_ptr(other_params = *p_next++ =
                     EC_GROUP_get_ecparameters(tmpg, NULL))
        || !TEST_ptr(tgroup = *g_next++ =
                      EC_GROUP_new_from_ecparameters(other_params))
        || !TEST_int_ne((tnid = EC_GROUP_get_curve_name(tgroup)), NID_undef)
        || !TEST_true(are_ec_nids_compatible(nid, tnid))
        || !TEST_int_eq(EC_GROUP_get_asn1_flag(tgroup),
                        OPENSSL_EC_EXPLICIT_CURVE)
        /* Check that if the cofactor is not set then it still matches */
        || !TEST_true(EC_GROUP_set_generator(tmpg, group_gen, group_order,
                                             NULL))
        || !TEST_ptr(other_params = *p_next++ =
                     EC_GROUP_get_ecparameters(tmpg, NULL))
        || !TEST_ptr(tgroup = *g_next++ =
                      EC_GROUP_new_from_ecparameters(other_params))
        || !TEST_int_ne((tnid = EC_GROUP_get_curve_name(tgroup)), NID_undef)
        || !TEST_true(are_ec_nids_compatible(nid, tnid))
        || !TEST_int_eq(EC_GROUP_get_asn1_flag(tgroup),
                        OPENSSL_EC_EXPLICIT_CURVE)
        /* check that restoring the generator passes */
        || !TEST_true(EC_GROUP_set_generator(tmpg, group_gen, group_order,
                                             group_cofactor))
        || !TEST_ptr(other_params = *p_next++ =
                     EC_GROUP_get_ecparameters(tmpg, NULL))
        || !TEST_ptr(tgroup = *g_next++ =
                      EC_GROUP_new_from_ecparameters(other_params))
        || !TEST_int_ne((tnid = EC_GROUP_get_curve_name(tgroup)), NID_undef)
        || !TEST_true(are_ec_nids_compatible(nid, tnid))
        || !TEST_int_eq(EC_GROUP_get_asn1_flag(tgroup),
                        OPENSSL_EC_EXPLICIT_CURVE))
        goto err;

    ret = 1;
err:
    for (g_next = &g_ary[0]; g_next < g_ary + OSSL_NELEM(g_ary); g_next++)
        EC_GROUP_free(*g_next);
    for (p_next = &p_ary[0]; p_next < p_ary + OSSL_NELEM(g_ary); p_next++)
        ECPARAMETERS_free(*p_next);
    ECPARAMETERS_free(params);
    EC_POINT_free(other_gen);
    EC_GROUP_free(tmpg);
    EC_GROUP_free(group);
    BN_CTX_end(bn_ctx);
    BN_CTX_free(bn_ctx);
    return ret;
}