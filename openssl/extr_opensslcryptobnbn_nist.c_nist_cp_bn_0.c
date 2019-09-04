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

__attribute__((used)) static void nist_cp_bn_0(BN_ULONG *dst, const BN_ULONG *src, int top, int max)
{
    int i;

#ifdef BN_DEBUG
    (void)ossl_assert(top <= max);
#endif
    for (i = 0; i < top; i++)
        dst[i] = src[i];
    for (; i < max; i++)
        dst[i] = 0;
}