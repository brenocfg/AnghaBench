#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int BN_ULONG ;

/* Variables and functions */
 int BN_MASK2 ; 
 int /*<<< orphan*/  assert (int) ; 

BN_ULONG bn_sub_words(BN_ULONG *r, const BN_ULONG *a, const BN_ULONG *b,
                      int n)
{
    BN_ULONG t1, t2;
    int c = 0;

    assert(n >= 0);
    if (n <= 0)
        return (BN_ULONG)0;

#ifndef OPENSSL_SMALL_FOOTPRINT
    while (n & ~3) {
        t1 = a[0];
        t2 = b[0];
        r[0] = (t1 - t2 - c) & BN_MASK2;
        if (t1 != t2)
            c = (t1 < t2);
        t1 = a[1];
        t2 = b[1];
        r[1] = (t1 - t2 - c) & BN_MASK2;
        if (t1 != t2)
            c = (t1 < t2);
        t1 = a[2];
        t2 = b[2];
        r[2] = (t1 - t2 - c) & BN_MASK2;
        if (t1 != t2)
            c = (t1 < t2);
        t1 = a[3];
        t2 = b[3];
        r[3] = (t1 - t2 - c) & BN_MASK2;
        if (t1 != t2)
            c = (t1 < t2);
        a += 4;
        b += 4;
        r += 4;
        n -= 4;
    }
#endif
    while (n) {
        t1 = a[0];
        t2 = b[0];
        r[0] = (t1 - t2 - c) & BN_MASK2;
        if (t1 != t2)
            c = (t1 < t2);
        a++;
        b++;
        r++;
        n--;
    }
    return c;
}