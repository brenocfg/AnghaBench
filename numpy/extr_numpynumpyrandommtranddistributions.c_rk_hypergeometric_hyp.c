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
typedef  int /*<<< orphan*/  rk_state ;

/* Variables and functions */
 scalar_t__ floor (double) ; 
 scalar_t__ min (long,long) ; 
 double rk_double (int /*<<< orphan*/ *) ; 

long rk_hypergeometric_hyp(rk_state *state, long good, long bad, long sample)
{
    long d1, K, Z;
    double d2, U, Y;

    d1 = bad + good - sample;
    d2 = (double)min(bad, good);

    Y = d2;
    K = sample;
    while (Y > 0.0)
    {
        U = rk_double(state);
        Y -= (long)floor(U + Y/(d1 + K));
        K--;
        if (K == 0) break;
    }
    Z = (long)(d2 - Y);
    if (good > bad) Z = sample - Z;
    return Z;
}