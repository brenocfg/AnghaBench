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
 double exp (double) ; 
 double rk_double (int /*<<< orphan*/ *) ; 

long rk_poisson_mult(rk_state *state, double lam)
{
    long X;
    double prod, U, enlam;

    enlam = exp(-lam);
    X = 0;
    prod = 1.0;
    while (1)
    {
        U = rk_double(state);
        prod *= U;
        if (prod > enlam)
        {
            X += 1;
        }
        else
        {
            return X;
        }
    }
}