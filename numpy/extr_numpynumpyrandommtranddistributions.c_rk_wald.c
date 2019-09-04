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
 double rk_double (int /*<<< orphan*/ *) ; 
 double rk_gauss (int /*<<< orphan*/ *) ; 
 double sqrt (int) ; 

double rk_wald(rk_state *state, double mean, double scale)
{
    double U, X, Y;
    double mu_2l;

    mu_2l = mean / (2*scale);
    Y = rk_gauss(state);
    Y = mean*Y*Y;
    X = mean + mu_2l*(Y - sqrt(4*scale*Y + Y*Y));
    U = rk_double(state);
    if (U <= mean/(mean+X))
    {
        return X;
    } else
    {
        return mean*mean/X;
    }
}