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
 scalar_t__ floor (int) ; 
 int log (double) ; 
 double rk_double (int /*<<< orphan*/ *) ; 

long rk_logseries(rk_state *state, double p)
{
    double q, r, U, V;
    long result;

    r = log(1.0 - p);

    while (1) {
        V = rk_double(state);
        if (V >= p) {
            return 1;
        }
        U = rk_double(state);
        q = 1.0 - exp(r*U);
        if (V <= q*q) {
            result = (long)floor(1 + log(V)/log(q));
            if (result < 1) {
                continue;
            }
            else {
                return result;
            }
        }
        if (V >= q) {
            return 1;
        }
        return 2;
    }
}