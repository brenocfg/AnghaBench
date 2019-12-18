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
struct TYPE_8__ {int top; scalar_t__* d; } ;
typedef  scalar_t__ BN_ULONG ;
typedef  scalar_t__ BN_ULLONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_BITS2 ; 
 scalar_t__ BN_BITS4 ; 
 scalar_t__ BN_MASK2 ; 
 scalar_t__ BN_MASK2l ; 
 scalar_t__ BN_div_word (TYPE_1__*,scalar_t__) ; 
 TYPE_1__* BN_dup (TYPE_1__ const*) ; 
 int /*<<< orphan*/  BN_free (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 

BN_ULONG BN_mod_word(const BIGNUM *a, BN_ULONG w)
{
#ifndef BN_LLONG
    BN_ULONG ret = 0;
#else
    BN_ULLONG ret = 0;
#endif
    int i;

    if (w == 0)
        return (BN_ULONG)-1;

#ifndef BN_LLONG
    /*
     * If |w| is too long and we don't have BN_ULLONG then we need to fall
     * back to using BN_div_word
     */
    if (w > ((BN_ULONG)1 << BN_BITS4)) {
        BIGNUM *tmp = BN_dup(a);
        if (tmp == NULL)
            return (BN_ULONG)-1;

        ret = BN_div_word(tmp, w);
        BN_free(tmp);

        return ret;
    }
#endif

    bn_check_top(a);
    w &= BN_MASK2;
    for (i = a->top - 1; i >= 0; i--) {
#ifndef BN_LLONG
        /*
         * We can assume here that | w <= ((BN_ULONG)1 << BN_BITS4) | and so
         * | ret < ((BN_ULONG)1 << BN_BITS4) | and therefore the shifts here are
         * safe and will not overflow
         */
        ret = ((ret << BN_BITS4) | ((a->d[i] >> BN_BITS4) & BN_MASK2l)) % w;
        ret = ((ret << BN_BITS4) | (a->d[i] & BN_MASK2l)) % w;
#else
        ret = (BN_ULLONG) (((ret << (BN_ULLONG) BN_BITS2) | a->d[i]) %
                           (BN_ULLONG) w);
#endif
    }
    return (BN_ULONG)ret;
}