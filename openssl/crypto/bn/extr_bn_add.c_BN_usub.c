#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int top; scalar_t__* d; scalar_t__ neg; } ;
typedef  scalar_t__ BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_F_BN_USUB ; 
 scalar_t__ BN_MASK2 ; 
 int /*<<< orphan*/  BN_R_ARG2_LT_ARG3 ; 
 int /*<<< orphan*/  BNerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 
 int /*<<< orphan*/  bn_pollute (TYPE_1__*) ; 
 scalar_t__ bn_sub_words (scalar_t__*,scalar_t__ const*,scalar_t__ const*,int) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,int) ; 

int BN_usub(BIGNUM *r, const BIGNUM *a, const BIGNUM *b)
{
    int max, min, dif;
    BN_ULONG t1, t2, borrow, *rp;
    const BN_ULONG *ap, *bp;

    bn_check_top(a);
    bn_check_top(b);

    max = a->top;
    min = b->top;
    dif = max - min;

    if (dif < 0) {              /* hmm... should not be happening */
        BNerr(BN_F_BN_USUB, BN_R_ARG2_LT_ARG3);
        return 0;
    }

    if (bn_wexpand(r, max) == NULL)
        return 0;

    ap = a->d;
    bp = b->d;
    rp = r->d;

    borrow = bn_sub_words(rp, ap, bp, min);
    ap += min;
    rp += min;

    while (dif) {
        dif--;
        t1 = *(ap++);
        t2 = (t1 - borrow) & BN_MASK2;
        *(rp++) = t2;
        borrow &= (t1 == 0);
    }

    while (max && *--rp == 0)
        max--;

    r->top = max;
    r->neg = 0;
    bn_pollute(r);

    return 1;
}