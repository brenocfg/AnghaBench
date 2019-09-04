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
 int log (double) ; 
 double pow (double,int) ; 
 double rk_double (int /*<<< orphan*/ *) ; 
 double rk_gauss (int /*<<< orphan*/ *) ; 
 double rk_standard_exponential (int /*<<< orphan*/ *) ; 
 int sqrt (int) ; 

double rk_standard_gamma(rk_state *state, double shape)
{
    double b, c;
    double U, V, X, Y;

    if (shape == 1.0)
    {
        return rk_standard_exponential(state);
    }
    else if (shape < 1.0)
    {
        for (;;)
        {
            U = rk_double(state);
            V = rk_standard_exponential(state);
            if (U <= 1.0 - shape)
            {
                X = pow(U, 1./shape);
                if (X <= V)
                {
                    return X;
                }
            }
            else
            {
                Y = -log((1-U)/shape);
                X = pow(1.0 - shape + shape*Y, 1./shape);
                if (X <= (V + Y))
                {
                    return X;
                }
            }
        }
    }
    else
    {
        b = shape - 1./3.;
        c = 1./sqrt(9*b);
        for (;;)
        {
            do
            {
                X = rk_gauss(state);
                V = 1.0 + c*X;
            } while (V <= 0.0);

            V = V*V*V;
            U = rk_double(state);
            if (U < 1.0 - 0.0331*(X*X)*(X*X)) return (b*V);
            if (log(U) < 0.5*X*X + b*(1. - V + log(V))) return (b*V);
        }
    }
}