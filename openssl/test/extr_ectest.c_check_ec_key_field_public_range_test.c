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
struct TYPE_2__ {int /*<<< orphan*/  nid; } ;
typedef  int /*<<< orphan*/  const EC_POINT ;
typedef  int /*<<< orphan*/  const EC_METHOD ;
typedef  int /*<<< orphan*/  const EC_KEY ;
typedef  int /*<<< orphan*/  const EC_GROUP ;
typedef  int /*<<< orphan*/  const BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_GF2m_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_add (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_new () ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_field (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_method_of (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_check_key (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_KEY_generate_key (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_KEY_get0_group (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_KEY_get0_public_key (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_KEY_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EC_KEY_set_public_key_affine_coordinates (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int EC_METHOD_get_field_type (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_get_affine_coordinates (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int NID_X9_62_characteristic_two_field ; 
 int NID_X9_62_prime_field ; 
 int /*<<< orphan*/  TEST_error (char*) ; 
 int /*<<< orphan*/  TEST_int_gt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_le (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* curves ; 

__attribute__((used)) static int check_ec_key_field_public_range_test(int id)
{
    int ret = 0, type = 0;
    const EC_POINT *pub = NULL;
    const EC_GROUP *group = NULL;
    const EC_METHOD *meth = NULL;
    const BIGNUM *field = NULL;
    BIGNUM *x = NULL, *y = NULL;
    EC_KEY *key = NULL;

    if (!TEST_ptr(x = BN_new())
            || !TEST_ptr(y = BN_new())
            || !TEST_ptr(key = EC_KEY_new_by_curve_name(curves[id].nid))
            || !TEST_ptr(group = EC_KEY_get0_group(key))
            || !TEST_ptr(meth = EC_GROUP_method_of(group))
            || !TEST_ptr(field = EC_GROUP_get0_field(group))
            || !TEST_int_gt(EC_KEY_generate_key(key), 0)
            || !TEST_int_gt(EC_KEY_check_key(key), 0)
            || !TEST_ptr(pub = EC_KEY_get0_public_key(key))
            || !TEST_int_gt(EC_POINT_get_affine_coordinates(group, pub, x, y,
                                                            NULL), 0))
        goto err;

    /*
     * Make the public point out of range by adding the field (which will still
     * be the same point on the curve). The add is different for char2 fields.
     */
    type = EC_METHOD_get_field_type(meth);
#ifndef OPENSSL_NO_EC2M
    if (type == NID_X9_62_characteristic_two_field) {
        /* test for binary curves */
        if (!TEST_true(BN_GF2m_add(x, x, field)))
            goto err;
    } else
#endif
    if (type == NID_X9_62_prime_field) {
        /* test for prime curves */
        if (!TEST_true(BN_add(x, x, field)))
            goto err;
    } else {
        /* this should never happen */
        TEST_error("Unsupported EC_METHOD field_type");
        goto err;
    }
    if (!TEST_int_le(EC_KEY_set_public_key_affine_coordinates(key, x, y), 0))
        goto err;

    ret = 1;
err:
    BN_free(x);
    BN_free(y);
    EC_KEY_free(key);
    return ret;
}