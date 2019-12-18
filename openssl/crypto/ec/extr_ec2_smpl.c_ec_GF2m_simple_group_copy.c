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
struct TYPE_4__ {int* poly; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  field; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int BN_BITS2 ; 
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_set_all_zero (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bn_wexpand (int /*<<< orphan*/ ,int) ; 

int ec_GF2m_simple_group_copy(EC_GROUP *dest, const EC_GROUP *src)
{
    if (!BN_copy(dest->field, src->field))
        return 0;
    if (!BN_copy(dest->a, src->a))
        return 0;
    if (!BN_copy(dest->b, src->b))
        return 0;
    dest->poly[0] = src->poly[0];
    dest->poly[1] = src->poly[1];
    dest->poly[2] = src->poly[2];
    dest->poly[3] = src->poly[3];
    dest->poly[4] = src->poly[4];
    dest->poly[5] = src->poly[5];
    if (bn_wexpand(dest->a, (int)(dest->poly[0] + BN_BITS2 - 1) / BN_BITS2) ==
        NULL)
        return 0;
    if (bn_wexpand(dest->b, (int)(dest->poly[0] + BN_BITS2 - 1) / BN_BITS2) ==
        NULL)
        return 0;
    bn_set_all_zero(dest->a);
    bn_set_all_zero(dest->b);
    return 1;
}