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
typedef  scalar_t__ BN_ULONG ;

/* Variables and functions */
 int /*<<< orphan*/  bn_add_words (scalar_t__*,scalar_t__*,scalar_t__*,int) ; 
 scalar_t__ bn_mul_add_words (scalar_t__*,scalar_t__ const*,int,scalar_t__ const) ; 
 scalar_t__ bn_mul_words (scalar_t__*,scalar_t__ const*,int,scalar_t__ const) ; 
 int /*<<< orphan*/  bn_sqr_words (scalar_t__*,scalar_t__ const*,int) ; 

void bn_sqr_normal(BN_ULONG *r, const BN_ULONG *a, int n, BN_ULONG *tmp)
{
    int i, j, max;
    const BN_ULONG *ap;
    BN_ULONG *rp;

    max = n * 2;
    ap = a;
    rp = r;
    rp[0] = rp[max - 1] = 0;
    rp++;
    j = n;

    if (--j > 0) {
        ap++;
        rp[j] = bn_mul_words(rp, ap, j, ap[-1]);
        rp += 2;
    }

    for (i = n - 2; i > 0; i--) {
        j--;
        ap++;
        rp[j] = bn_mul_add_words(rp, ap, j, ap[-1]);
        rp += 2;
    }

    bn_add_words(r, r, r, max);

    /* There will not be a carry */

    bn_sqr_words(tmp, a, n);

    bn_add_words(r, r, tmp, max);
}