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
struct TYPE_4__ {int /*<<< orphan*/  a_is_minus3; int /*<<< orphan*/  b; int /*<<< orphan*/  a; int /*<<< orphan*/  field; } ;
typedef  TYPE_1__ EC_GROUP ;

/* Variables and functions */
 int /*<<< orphan*/  BN_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int ec_GFp_simple_group_copy(EC_GROUP *dest, const EC_GROUP *src)
{
    if (!BN_copy(dest->field, src->field))
        return 0;
    if (!BN_copy(dest->a, src->a))
        return 0;
    if (!BN_copy(dest->b, src->b))
        return 0;

    dest->a_is_minus3 = src->a_is_minus3;

    return 1;
}