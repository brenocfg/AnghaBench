#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int top; int /*<<< orphan*/ * d; } ;
typedef  TYPE_1__ BIGNUM ;

/* Variables and functions */
 int BN_BITS2 ; 
 scalar_t__ BN_is_zero (TYPE_1__ const*) ; 
 int BN_num_bits_word (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bn_check_top (TYPE_1__ const*) ; 

int BN_num_bits(const BIGNUM *a)
{
    int i = a->top - 1;
    bn_check_top(a);

    if (BN_is_zero(a))
        return 0;
    return ((i * BN_BITS2) + BN_num_bits_word(a->d[i]));
}