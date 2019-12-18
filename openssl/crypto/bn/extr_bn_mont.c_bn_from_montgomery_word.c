#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtop ;
struct TYPE_8__ {int top; int* d; int /*<<< orphan*/  neg; int /*<<< orphan*/  flags; } ;
struct TYPE_7__ {int* n0; TYPE_2__ N; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BN_MONT_CTX ;
typedef  TYPE_2__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_FLG_FIXED_TOP ; 
 int BN_MASK2 ; 
 int bn_mul_add_words (int*,int*,int,int) ; 
 scalar_t__ bn_sub_words (int*,int*,int*,int) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_2__*,int) ; 

__attribute__((used)) static int bn_from_montgomery_word(BIGNUM *ret, BIGNUM *r, BN_MONT_CTX *mont)
{
    BIGNUM *n;
    BN_ULONG *ap, *np, *rp, n0, v, carry;
    int nl, max, i;
    unsigned int rtop;

    n = &(mont->N);
    nl = n->top;
    if (nl == 0) {
        ret->top = 0;
        return 1;
    }

    max = (2 * nl);             /* carry is stored separately */
    if (bn_wexpand(r, max) == NULL)
        return 0;

    r->neg ^= n->neg;
    np = n->d;
    rp = r->d;

    /* clear the top words of T */
    for (rtop = r->top, i = 0; i < max; i++) {
        v = (BN_ULONG)0 - ((i - rtop) >> (8 * sizeof(rtop) - 1));
        rp[i] &= v;
    }

    r->top = max;
    r->flags |= BN_FLG_FIXED_TOP;
    n0 = mont->n0[0];

    /*
     * Add multiples of |n| to |r| until R = 2^(nl * BN_BITS2) divides it. On
     * input, we had |r| < |n| * R, so now |r| < 2 * |n| * R. Note that |r|
     * includes |carry| which is stored separately.
     */
    for (carry = 0, i = 0; i < nl; i++, rp++) {
        v = bn_mul_add_words(rp, np, nl, (rp[0] * n0) & BN_MASK2);
        v = (v + carry + rp[nl]) & BN_MASK2;
        carry |= (v != rp[nl]);
        carry &= (v <= rp[nl]);
        rp[nl] = v;
    }

    if (bn_wexpand(ret, nl) == NULL)
        return 0;
    ret->top = nl;
    ret->flags |= BN_FLG_FIXED_TOP;
    ret->neg = r->neg;

    rp = ret->d;

    /*
     * Shift |nl| words to divide by R. We have |ap| < 2 * |n|. Note that |ap|
     * includes |carry| which is stored separately.
     */
    ap = &(r->d[nl]);

    carry -= bn_sub_words(rp, ap, np, nl);
    /*
     * |carry| is -1 if |ap| - |np| underflowed or zero if it did not. Note
     * |carry| cannot be 1. That would imply the subtraction did not fit in
     * |nl| words, and we know at most one subtraction is needed.
     */
    for (i = 0; i < nl; i++) {
        rp[i] = (carry & ap[i]) | (~carry & rp[i]);
        ap[i] = 0;
    }

    return 1;
}