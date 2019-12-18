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
typedef  int /*<<< orphan*/  BIGNUM ;

/* Variables and functions */
 scalar_t__ BN_set_bit (int /*<<< orphan*/ *,int const) ; 
 int /*<<< orphan*/  BN_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bn_check_top (int /*<<< orphan*/ *) ; 

int BN_GF2m_arr2poly(const int p[], BIGNUM *a)
{
    int i;

    bn_check_top(a);
    BN_zero(a);
    for (i = 0; p[i] != -1; i++) {
        if (BN_set_bit(a, p[i]) == 0)
            return 0;
    }
    bn_check_top(a);

    return 1;
}