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
 int BN_MUL_LOW_RECURSIVE_SIZE_NORMAL ; 
 int /*<<< orphan*/  bn_add_words (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bn_mul_low_normal (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bn_mul_recursive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void bn_mul_low_recursive(BN_ULONG *r, BN_ULONG *a, BN_ULONG *b, int n2,
                          BN_ULONG *t)
{
    int n = n2 / 2;

    bn_mul_recursive(r, a, b, n, 0, 0, &(t[0]));
    if (n >= BN_MUL_LOW_RECURSIVE_SIZE_NORMAL) {
        bn_mul_low_recursive(&(t[0]), &(a[0]), &(b[n]), n, &(t[n2]));
        bn_add_words(&(r[n]), &(r[n]), &(t[0]), n);
        bn_mul_low_recursive(&(t[0]), &(a[n]), &(b[0]), n, &(t[n2]));
        bn_add_words(&(r[n]), &(r[n]), &(t[0]), n);
    } else {
        bn_mul_low_normal(&(t[0]), &(a[0]), &(b[n]), n);
        bn_mul_low_normal(&(t[n]), &(a[n]), &(b[0]), n);
        bn_add_words(&(r[n]), &(r[n]), &(t[0]), n);
        bn_add_words(&(r[n]), &(r[n]), &(t[n]), n);
    }
}