#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * field_data2; int /*<<< orphan*/ * field_data1; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MONT_CTX_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BN_clear_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ec_GFp_simple_group_clear_finish (TYPE_1__*) ; 

void ec_GFp_mont_group_clear_finish(EC_GROUP *group)
{
    BN_MONT_CTX_free(group->field_data1);
    group->field_data1 = NULL;
    BN_clear_free(group->field_data2);
    group->field_data2 = NULL;
    ec_GFp_simple_group_clear_finish(group);
}