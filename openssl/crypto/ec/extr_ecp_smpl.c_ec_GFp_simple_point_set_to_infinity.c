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
struct TYPE_3__ {int /*<<< orphan*/  Z; scalar_t__ Z_is_one; } ;
typedef  TYPE_1__ EC_POINT ;
typedef  int /*<<< orphan*/  EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ ) ; 

int ec_GFp_simple_point_set_to_infinity(const EC_GROUP *group,
                                        EC_POINT *point)
{
    point->Z_is_one = 0;
    BN_zero(point->Z);
    return 1;
}