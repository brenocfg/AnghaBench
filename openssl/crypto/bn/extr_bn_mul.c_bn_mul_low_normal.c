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
 int /*<<< orphan*/  bn_mul_add_words (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_mul_words (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

void bn_mul_low_normal(BN_ULONG *r, BN_ULONG *a, BN_ULONG *b, int n)
{
    bn_mul_words(r, a, n, b[0]);

    for (;;) {
        if (--n <= 0)
            return;
        bn_mul_add_words(&(r[1]), a, n, b[1]);
        if (--n <= 0)
            return;
        bn_mul_add_words(&(r[2]), a, n, b[2]);
        if (--n <= 0)
            return;
        bn_mul_add_words(&(r[3]), a, n, b[3]);
        if (--n <= 0)
            return;
        bn_mul_add_words(&(r[4]), a, n, b[4]);
        r += 4;
        b += 4;
    }
}