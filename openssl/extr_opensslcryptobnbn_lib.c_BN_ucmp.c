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
struct TYPE_5__ {int top; scalar_t__* d; } ;
typedef  scalar_t__ BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 

int BN_ucmp(const BIGNUM *a, const BIGNUM *b)
{
    int i;
    BN_ULONG t1, t2, *ap, *bp;

    bn_check_top(a);
    bn_check_top(b);

    i = a->top - b->top;
    if (i != 0)
        return i;
    ap = a->d;
    bp = b->d;
    for (i = a->top - 1; i >= 0; i--) {
        t1 = ap[i];
        t2 = bp[i];
        if (t1 != t2)
            return ((t1 > t2) ? 1 : -1);
    }
    return 0;
}