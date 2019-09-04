#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ a_is_minus3; int /*<<< orphan*/ * b; int /*<<< orphan*/ * a; int /*<<< orphan*/ * field; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  BN_free (int /*<<< orphan*/ *) ; 
 void* BN_new () ; 

int ec_GFp_simple_group_init(EC_GROUP *group)
{
    group->field = BN_new();
    group->a = BN_new();
    group->b = BN_new();
    if (group->field == NULL || group->a == NULL || group->b == NULL) {
        BN_free(group->field);
        BN_free(group->a);
        BN_free(group->b);
        return 0;
    }
    group->a_is_minus3 = 0;
    return 1;
}