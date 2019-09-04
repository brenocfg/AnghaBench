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
 long rk_binomial_btpe (int /*<<< orphan*/ *,long,double) ; 
 long rk_binomial_inversion (int /*<<< orphan*/ *,long,double) ; 

long rk_binomial(rk_state *state, long n, double p)
{
    double q;

    if (p <= 0.5)
    {
        if (p*n <= 30.0)
        {
            return rk_binomial_inversion(state, n, p);
        }
        else
        {
            return rk_binomial_btpe(state, n, p);
        }
    }
    else
    {
        q = 1.0-p;
        if (q*n <= 30.0)
        {
            return n - rk_binomial_inversion(state, n, q);
        }
        else
        {
            return n - rk_binomial_btpe(state, n, q);
        }
    }

}