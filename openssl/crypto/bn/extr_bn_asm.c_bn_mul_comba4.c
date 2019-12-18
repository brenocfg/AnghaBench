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
 int /*<<< orphan*/  mul_add_c (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 

void bn_mul_comba4(BN_ULONG *r, BN_ULONG *a, BN_ULONG *b)
{
    BN_ULONG c1, c2, c3;

    c1 = 0;
    c2 = 0;
    c3 = 0;
    mul_add_c(a[0], b[0], c1, c2, c3);
    r[0] = c1;
    c1 = 0;
    mul_add_c(a[0], b[1], c2, c3, c1);
    mul_add_c(a[1], b[0], c2, c3, c1);
    r[1] = c2;
    c2 = 0;
    mul_add_c(a[2], b[0], c3, c1, c2);
    mul_add_c(a[1], b[1], c3, c1, c2);
    mul_add_c(a[0], b[2], c3, c1, c2);
    r[2] = c3;
    c3 = 0;
    mul_add_c(a[0], b[3], c1, c2, c3);
    mul_add_c(a[1], b[2], c1, c2, c3);
    mul_add_c(a[2], b[1], c1, c2, c3);
    mul_add_c(a[3], b[0], c1, c2, c3);
    r[3] = c1;
    c1 = 0;
    mul_add_c(a[3], b[1], c2, c3, c1);
    mul_add_c(a[2], b[2], c2, c3, c1);
    mul_add_c(a[1], b[3], c2, c3, c1);
    r[4] = c2;
    c2 = 0;
    mul_add_c(a[2], b[3], c3, c1, c2);
    mul_add_c(a[3], b[2], c3, c1, c2);
    r[5] = c3;
    c3 = 0;
    mul_add_c(a[3], b[3], c1, c2, c3);
    r[6] = c1;
    r[7] = c2;
}