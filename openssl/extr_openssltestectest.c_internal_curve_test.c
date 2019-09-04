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
 int /*<<< orphan*/  EC_GROUP_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EC_GROUP_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * EC_GROUP_new_by_curve_name (int) ; 
 int /*<<< orphan*/  OBJ_nid2sn (int) ; 
 int /*<<< orphan*/  TEST_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TEST_ptr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TEST_true (int /*<<< orphan*/ ) ; 
 TYPE_1__* curves ; 

__attribute__((used)) static int internal_curve_test(int n)
{
    EC_GROUP *group = NULL;
    int nid = curves[n].nid;

    if (!TEST_ptr(group = EC_GROUP_new_by_curve_name(nid))) {
        TEST_info("EC_GROUP_new_curve_name() failed with curve %s\n",
                  OBJ_nid2sn(nid));
        return 0;
    }
    if (!TEST_true(EC_GROUP_check(group, NULL))) {
        TEST_info("EC_GROUP_check() failed with curve %s\n", OBJ_nid2sn(nid));
        EC_GROUP_free(group);
        return 0;
    }
    EC_GROUP_free(group);
    return 1;
}