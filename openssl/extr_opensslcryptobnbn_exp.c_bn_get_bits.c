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
struct TYPE_3__ {int top; int* d; } ;
typedef  int BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 int BN_MASK2 ; 

__attribute__((used)) static BN_ULONG bn_get_bits(const BIGNUM *a, int bitpos)
{
    BN_ULONG ret = 0;
    int wordpos;

    wordpos = bitpos / BN_BITS2;
    bitpos %= BN_BITS2;
    if (wordpos >= 0 && wordpos < a->top) {
        ret = a->d[wordpos] & BN_MASK2;
        if (bitpos) {
            ret >>= bitpos;
            if (++wordpos < a->top)
                ret |= a->d[wordpos] << (BN_BITS2 - bitpos);
        }
    }

    return ret & BN_MASK2;
}