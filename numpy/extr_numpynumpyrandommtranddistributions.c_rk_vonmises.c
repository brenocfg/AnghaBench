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
 int M_PI ; 
 double acos (double) ; 
 double cos (int) ; 
 double fabs (double) ; 
 int fmod (double,int) ; 
 int log (double) ; 
 int rk_double (int /*<<< orphan*/ *) ; 
 double sqrt (int) ; 

double rk_vonmises(rk_state *state, double mu, double kappa)
{
    double s;
    double U, V, W, Y, Z;
    double result, mod;
    int neg;

    if (kappa < 1e-8)
    {
        return M_PI * (2*rk_double(state)-1);
    }
    else
    {
        /* with double precision rho is zero until 1.4e-8 */
        if (kappa < 1e-5) {
            /*
             * second order taylor expansion around kappa = 0
             * precise until relatively large kappas as second order is 0
             */
            s = (1./kappa + kappa);
        }
        else {
            double r = 1 + sqrt(1 + 4*kappa*kappa);
            double rho = (r - sqrt(2*r)) / (2*kappa);
            s = (1 + rho*rho)/(2*rho);
        }

        while (1)
        {
        U = rk_double(state);
            Z = cos(M_PI*U);
            W = (1 + s*Z)/(s + Z);
            Y = kappa * (s - W);
            V = rk_double(state);
            if ((Y*(2-Y) - V >= 0) || (log(Y/V)+1 - Y >= 0))
            {
                break;
            }
        }

        U = rk_double(state);

        result = acos(W);
        if (U < 0.5)
        {
        result = -result;
        }
        result += mu;
        neg = (result < 0);
        mod = fabs(result);
        mod = (fmod(mod+M_PI, 2*M_PI)-M_PI);
        if (neg)
        {
            mod *= -1;
        }

        return mod;
    }
}