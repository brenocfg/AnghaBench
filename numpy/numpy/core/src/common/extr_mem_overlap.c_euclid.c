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
typedef  int npy_int64 ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
euclid(npy_int64 a1, npy_int64 a2, npy_int64 *a_gcd, npy_int64 *gamma, npy_int64 *epsilon)
{
    npy_int64 gamma1, gamma2, epsilon1, epsilon2, r;

    assert(a1 > 0);
    assert(a2 > 0);

    gamma1 = 1;
    gamma2 = 0;
    epsilon1 = 0;
    epsilon2 = 1;

    /* The numbers remain bounded by |a1|, |a2| during
       the iteration, so no integer overflows */
    while (1) {
        if (a2 > 0) {
            r = a1/a2;
            a1 -= r*a2;
            gamma1 -= r*gamma2;
            epsilon1 -= r*epsilon2;
        }
        else {
            *a_gcd = a1;
            *gamma = gamma1;
            *epsilon = epsilon1;
            break;
        }

        if (a1 > 0) {
            r = a2/a1;
            a2 -= r*a1;
            gamma2 -= r*gamma1;
            epsilon2 -= r*epsilon1;
        }
        else {
            *a_gcd = a2;
            *gamma = gamma2;
            *epsilon = epsilon2;
            break;
        }
    }
}