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
typedef  int /*<<< orphan*/  EC_GROUP ;
typedef  int /*<<< orphan*/  ECPARAMETERS ;
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  ECPARAMETERS_free (int /*<<< orphan*/ *) ; 
 int EC_GROUP_check_named_curve (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_get_ecparameters (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int) ; 
 int /*<<< orphan*/ * EC_GROUP_new_from_ecparameters (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_int_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_int_gt (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__* curves ; 

__attribute__((used)) static int check_named_curve_lookup_test(int id)
{
    int ret = 0, nid, rv = 0;
    EC_GROUP *g = NULL , *ga = NULL;
    ECPARAMETERS *p = NULL, *pa = NULL;
    BN_CTX *ctx = NULL;

    /* Do some setup */
    nid = curves[id].nid;
    if (!TEST_ptr(ctx = BN_CTX_new())
        || !TEST_ptr(g = EC_GROUP_new_by_curve_name(nid))
        || !TEST_ptr(p = EC_GROUP_get_ecparameters(g, NULL)))
        goto err;

    /* replace with group from explicit parameters */
    EC_GROUP_free(g);
    if (!TEST_ptr(g = EC_GROUP_new_from_ecparameters(p)))
        goto err;

    if (!TEST_int_gt(rv = EC_GROUP_check_named_curve(g, 0, NULL), 0))
        goto err;
    if (rv != nid) {
        /*
         * Found an alias:
         * fail if the returned nid is not an alias of the original group.
         *
         * The comparison here is done by comparing two explicit
         * parameter EC_GROUPs with EC_GROUP_cmp(), to ensure the
         * comparison happens with unnamed EC_GROUPs using the same
         * EC_METHODs.
         */
        if (!TEST_ptr(ga = EC_GROUP_new_by_curve_name(rv))
                || !TEST_ptr(pa = EC_GROUP_get_ecparameters(ga, NULL)))
            goto err;

        /* replace with group from explicit parameters, then compare */
        EC_GROUP_free(ga);
        if (!TEST_ptr(ga = EC_GROUP_new_from_ecparameters(pa))
                || !TEST_int_eq(EC_GROUP_cmp(g, ga, ctx), 0))
            goto err;
    }

    ret = 1;

 err:
    EC_GROUP_free(g);
    EC_GROUP_free(ga);
    ECPARAMETERS_free(p);
    ECPARAMETERS_free(pa);
    BN_CTX_free(ctx);

    return ret;
}