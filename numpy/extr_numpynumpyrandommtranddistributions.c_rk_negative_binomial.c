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
 double rk_gamma (int /*<<< orphan*/ *,double,int) ; 
 long rk_poisson (int /*<<< orphan*/ *,double) ; 

long rk_negative_binomial(rk_state *state, double n, double p)
{
    double Y;

    Y = rk_gamma(state, n, (1-p)/p);
    return rk_poisson(state, Y);
}