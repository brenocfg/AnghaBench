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
struct TYPE_4__ {int /*<<< orphan*/  curve_name; int /*<<< orphan*/  Z_is_one; int /*<<< orphan*/  Z; int /*<<< orphan*/  Y; int /*<<< orphan*/  X; } ;
typedef  TYPE_1__ EC_POINT ;

/* Variables and functions */
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ec_GF2m_simple_point_copy(EC_POINT *dest, const EC_POINT *src)
{
    if (!BN_copy(dest->X, src->X))
        return 0;
    if (!BN_copy(dest->Y, src->Y))
        return 0;
    if (!BN_copy(dest->Z, src->Z))
        return 0;
    dest->Z_is_one = src->Z_is_one;
    dest->curve_name = src->curve_name;

    return 1;
}