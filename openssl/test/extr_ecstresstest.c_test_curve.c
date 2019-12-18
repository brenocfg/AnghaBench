#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_hex2bn (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BN_print (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_get0_generator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EC_POINT_dup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  NID_X9_62_prime256v1 ; 
 int /*<<< orphan*/  TEST_BN_eq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  kP256DefaultResult ; 
 int /*<<< orphan*/  num_repeats ; 
 scalar_t__ print_mode ; 
 int /*<<< orphan*/ * walk_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int test_curve(void)
{
    EC_GROUP *group = NULL;
    EC_POINT *point = NULL;
    BIGNUM *result = NULL, *expected_result = NULL;
    int ret = 0;

    /*
     * We currently hard-code P-256, though adaptation to other curves.
     * would be straightforward.
     */
    if (!TEST_ptr(group = EC_GROUP_new_by_curve_name(NID_X9_62_prime256v1))
            || !TEST_ptr(point = EC_POINT_dup(EC_GROUP_get0_generator(group),
                                              group))
            || !TEST_ptr(result = walk_curve(group, point, num_repeats)))
        return 0;

    if (print_mode) {
        BN_print(bio_out, result);
        BIO_printf(bio_out, "\n");
        ret = 1;
    } else {
        if (!TEST_true(BN_hex2bn(&expected_result, kP256DefaultResult))
                || !TEST_ptr(expected_result)
                || !TEST_BN_eq(result, expected_result))
            goto err;
        ret = 1;
    }

err:
    EC_GROUP_free(group);
    EC_POINT_free(point);
    BN_free(result);
    BN_free(expected_result);
    return ret;
}