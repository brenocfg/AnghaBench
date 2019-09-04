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
 double rk_gauss (int /*<<< orphan*/ *) ; 
 double rk_standard_gamma (int /*<<< orphan*/ *,double) ; 
 double sqrt (double) ; 

double rk_standard_t(rk_state *state, double df)
{
    double N, G, X;

    N = rk_gauss(state);
    G = rk_standard_gamma(state, df/2);
    X = sqrt(df/2)*N/sqrt(G);
    return X;
}