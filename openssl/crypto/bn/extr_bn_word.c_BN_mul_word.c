#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ top; int /*<<< orphan*/ * d; } ;
typedef  int /*<<< orphan*/  BN_ULONG ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int /*<<< orphan*/  BN_MASK2 ; 
 int /*<<< orphan*/  BN_zero (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__*) ; 
 int /*<<< orphan*/  bn_mul_words (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bn_wexpand (TYPE_1__*,scalar_t__) ; 

int BN_mul_word(BIGNUM *a, BN_ULONG w)
{
    BN_ULONG ll;

    bn_check_top(a);
    w &= BN_MASK2;
    if (a->top) {
        if (w == 0)
            BN_zero(a);
        else {
            ll = bn_mul_words(a->d, a->d, a->top, w);
            if (ll) {
                if (bn_wexpand(a, a->top + 1) == NULL)
                    return 0;
                a->d[a->top++] = ll;
            }
        }
    }
    bn_check_top(a);
    return 1;
}