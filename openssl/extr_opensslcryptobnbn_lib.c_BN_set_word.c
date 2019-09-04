#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int top; int /*<<< orphan*/  flags; scalar_t__* d; scalar_t__ neg; } ;
typedef  scalar_t__ BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_FIXED_TOP ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 
 int /*<<< orphan*/ * bn_expand (TYPE_1__*,int) ; 

int BN_set_word(BIGNUM *a, BN_ULONG w)
{
    bn_check_top(a);
    if (bn_expand(a, (int)sizeof(BN_ULONG) * 8) == NULL)
        return 0;
    a->neg = 0;
    a->d[0] = w;
    a->top = (w ? 1 : 0);
    a->flags &= ~BN_FLG_FIXED_TOP;
    bn_check_top(a);
    return 1;
}