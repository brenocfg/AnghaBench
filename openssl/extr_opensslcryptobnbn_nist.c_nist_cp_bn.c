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
typedef  int /*<<< orphan*/  BN_ULONG ;

/* Variables and functions */

__attribute__((used)) static void nist_cp_bn(BN_ULONG *dst, const BN_ULONG *src, int top)
{
    int i;

    for (i = 0; i < top; i++)
        dst[i] = src[i];
}