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
struct TYPE_2__ {int nid; } ;
typedef  int /*<<< orphan*/  const EC_POINT ;
typedef  int /*<<< orphan*/  const EC_GROUP ;
typedef  int /*<<< orphan*/  const BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* BN_CTX_new () ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_get0_generator (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  const* EC_GROUP_new_by_curve_name (int) ; 
 int /*<<< orphan*/  const* EC_POINT_dup (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EC_POINT_free (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  POINT_CONVERSION_COMPRESSED ; 
 int /*<<< orphan*/  POINT_CONVERSION_HYBRID ; 
 int /*<<< orphan*/  POINT_CONVERSION_UNCOMPRESSED ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* curves ; 
 int /*<<< orphan*/  ec_point_hex2point_test_helper (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int ec_point_hex2point_test(int id)
{
    int ret = 0, nid;
    EC_GROUP *group = NULL;
    const EC_POINT *G = NULL;
    EC_POINT *P = NULL;
    BN_CTX * bnctx = NULL;

    /* Do some setup */
    nid = curves[id].nid;
    if (!TEST_ptr(bnctx = BN_CTX_new())
            || !TEST_ptr(group = EC_GROUP_new_by_curve_name(nid))
            || !TEST_ptr(G = EC_GROUP_get0_generator(group))
            || !TEST_ptr(P = EC_POINT_dup(G, group)))
        goto err;

    if (!TEST_true(ec_point_hex2point_test_helper(group, P,
                                                  POINT_CONVERSION_COMPRESSED,
                                                  bnctx))
            || !TEST_true(ec_point_hex2point_test_helper(group, NULL,
                                                         POINT_CONVERSION_COMPRESSED,
                                                         bnctx))
            || !TEST_true(ec_point_hex2point_test_helper(group, P,
                                                         POINT_CONVERSION_UNCOMPRESSED,
                                                         bnctx))
            || !TEST_true(ec_point_hex2point_test_helper(group, NULL,
                                                         POINT_CONVERSION_UNCOMPRESSED,
                                                         bnctx))
            || !TEST_true(ec_point_hex2point_test_helper(group, P,
                                                         POINT_CONVERSION_HYBRID,
                                                         bnctx))
            || !TEST_true(ec_point_hex2point_test_helper(group, NULL,
                                                         POINT_CONVERSION_HYBRID,
                                                         bnctx)))
        goto err;

    ret = 1;

 err:
    EC_POINT_free(P);
    EC_GROUP_free(group);
    BN_CTX_free(bnctx);

    return ret;
}