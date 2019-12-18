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

/* Variables and functions */
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 TYPE_1__* curves ; 
 int group_order_tests (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int internal_curve_test_method(int n)
{
    int r, nid = curves[n].nid;
    EC_GROUP *group;

    if (!TEST_ptr(group = EC_GROUP_new_by_curve_name(nid))) {
        TEST_info("Curve %s failed\n", OBJ_nid2sn(nid));
        return 0;
    }
    r = group_order_tests(group);
    EC_GROUP_free(group);
    return r;
}