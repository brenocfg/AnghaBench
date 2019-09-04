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
 double rk_chisquare (int /*<<< orphan*/ *,double) ; 
 double rk_gauss (int /*<<< orphan*/ *) ; 
 long rk_poisson (int /*<<< orphan*/ *,double) ; 
 double sqrt (double) ; 

double rk_noncentral_chisquare(rk_state *state, double df, double nonc)
{
    if (nonc == 0){
        return rk_chisquare(state, df);
    }
    if(1 < df)
    {
        const double Chi2 = rk_chisquare(state, df - 1);
        const double N = rk_gauss(state) + sqrt(nonc);
        return Chi2 + N*N;
    }
    else
    {
        const long i = rk_poisson(state, nonc / 2.0);
        return rk_chisquare(state, df + 2 * i);
    }
}