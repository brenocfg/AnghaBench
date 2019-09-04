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
struct TYPE_4__ {int a_is_minus3; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int ec_GFp_simple_group_init (TYPE_1__*) ; 

int ec_GFp_nistp224_group_init(EC_GROUP *group)
{
    int ret;
    ret = ec_GFp_simple_group_init(group);
    group->a_is_minus3 = 1;
    return ret;
}