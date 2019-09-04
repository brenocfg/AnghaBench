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
 double fabs (double) ; 
 scalar_t__ floor (int) ; 
 double log (double) ; 
 double loggam (long) ; 
 double rk_double (int /*<<< orphan*/ *) ; 
 double sqrt (double) ; 

long rk_poisson_ptrs(rk_state *state, double lam)
{
    long k;
    double U, V, slam, loglam, a, b, invalpha, vr, us;

    slam = sqrt(lam);
    loglam = log(lam);
    b = 0.931 + 2.53*slam;
    a = -0.059 + 0.02483*b;
    invalpha = 1.1239 + 1.1328/(b-3.4);
    vr = 0.9277 - 3.6224/(b-2);

    while (1)
    {
        U = rk_double(state) - 0.5;
        V = rk_double(state);
        us = 0.5 - fabs(U);
        k = (long)floor((2*a/us + b)*U + lam + 0.43);
        if ((us >= 0.07) && (V <= vr))
        {
            return k;
        }
        if ((k < 0) ||
            ((us < 0.013) && (V > us)))
        {
            continue;
        }
        if ((log(V) + log(invalpha) - log(a/(us*us)+b)) <=
            (-lam + k*loglam - loggam(k+1)))
        {
            return k;
        }


    }

}