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
struct TYPE_3__ {int* d; int top; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int BN_MASK2 ; 
 int BN_num_bits_word (int) ; 

__attribute__((used)) static int bn_left_align(BIGNUM *num)
{
    BN_ULONG *d = num->d, n, m, rmask;
    int top = num->top;
    int rshift = BN_num_bits_word(d[top - 1]), lshift, i;

    lshift = BN_BITS2 - rshift;
    rshift %= BN_BITS2;            /* say no to undefined behaviour */
    rmask = (BN_ULONG)0 - rshift;  /* rmask = 0 - (rshift != 0) */
    rmask |= rmask >> 8;

    for (i = 0, m = 0; i < top; i++) {
        n = d[i];
        d[i] = ((n << lshift) | m) & BN_MASK2;
        m = (n >> rshift) & rmask;
    }

    return lshift;
}