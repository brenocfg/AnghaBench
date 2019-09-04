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
 double log (double) ; 
 double pow (double,double) ; 
 double rk_double (int /*<<< orphan*/ *) ; 
 double rk_standard_gamma (int /*<<< orphan*/ *,double) ; 

double rk_beta(rk_state *state, double a, double b)
{
    double Ga, Gb;

    if ((a <= 1.0) && (b <= 1.0))
    {
        double U, V, X, Y;
        /* Use Johnk's algorithm */

        while (1)
        {
            U = rk_double(state);
            V = rk_double(state);
            X = pow(U, 1.0/a);
            Y = pow(V, 1.0/b);

            if ((X + Y) <= 1.0)
            {
                if (X +Y > 0)
                {
                    return X / (X + Y);
                }
                else
                {
                    double logX = log(U) / a;
                    double logY = log(V) / b;
                    double logM = logX > logY ? logX : logY;
                    logX -= logM;
                    logY -= logM;

                    return exp(logX - log(exp(logX) + exp(logY)));
                }
            }
        }
    }
    else
    {
        Ga = rk_standard_gamma(state, a);
        Gb = rk_standard_gamma(state, b);
        return Ga/(Ga + Gb);
    }
}