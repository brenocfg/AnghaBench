#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int has_binomial; long nsave; double psave; double q; double r; double c; long m; } ;
typedef  TYPE_1__ rk_state ;

/* Variables and functions */
 double exp (long) ; 
 long log (double) ; 
 long min (long,double) ; 
 double rk_double (TYPE_1__*) ; 
 double sqrt (double) ; 

long rk_binomial_inversion(rk_state *state, long n, double p)
{
    double q, qn, np, px, U;
    long X, bound;

    if (!(state->has_binomial) ||
         (state->nsave != n) ||
         (state->psave != p))
    {
        state->nsave = n;
        state->psave = p;
        state->has_binomial = 1;
        state->q = q = 1.0 - p;
        state->r = qn = exp(n * log(q));
        state->c = np = n*p;
        state->m = bound = min(n, np + 10.0*sqrt(np*q + 1));
    } else
    {
        q = state->q;
        qn = state->r;
        np = state->c;
        bound = state->m;
    }
    X = 0;
    px = qn;
    U = rk_double(state);
    while (U > px)
    {
        X++;
        if (X > bound)
        {
            X = 0;
            px = qn;
            U = rk_double(state);
        } else
        {
            U -= px;
            px  = ((n-X+1) * p * px)/(X*q);
        }
    }
    return X;
}