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
 double LONG_MAX ; 
 double floor (double) ; 
 double pow (double,double) ; 
 double rk_double (int /*<<< orphan*/ *) ; 

long rk_zipf(rk_state *state, double a)
{
    double am1, b;

    am1 = a - 1.0;
    b = pow(2.0, am1);
    while (1) {
        double T, U, V, X;

        U = 1.0 - rk_double(state);
        V = rk_double(state);
        X = floor(pow(U, -1.0/am1));
        /*
         * The real result may be above what can be represented in a signed
         * long. Since this is a straightforward rejection algorithm, we can
         * just reject this value. This function then models a Zipf
         * distribution truncated to sys.maxint.
         */
        if (X > LONG_MAX || X < 1.0) {
            continue;
        }

        T = pow(1.0 + 1.0/X, am1);
        if (V*X*(T - 1.0)/(b - 1.0) <= T/b) {
            return (long)X;
        }
    }
}