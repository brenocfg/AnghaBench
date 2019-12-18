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
typedef  int /*<<< orphan*/  BN_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  BN_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * BN_CTX_new () ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__* curves ; 
 int /*<<< orphan*/  group_field_tests (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int field_tests_default(int n)
{
    BN_CTX *ctx = NULL;
    EC_GROUP *group = NULL;
    int nid = curves[n].nid;
    int ret = 0;

    TEST_info("Testing curve %s\n", OBJ_nid2sn(nid));

    if (!TEST_ptr(group = EC_GROUP_new_by_curve_name(nid))
        || !TEST_ptr(ctx = BN_CTX_new())
        || !group_field_tests(group, ctx))
        goto err;

    ret = 1;
 err:
    if (group != NULL)
        EC_GROUP_free(group);
    if (ctx != NULL)
        BN_CTX_free(ctx);
    return ret;
}