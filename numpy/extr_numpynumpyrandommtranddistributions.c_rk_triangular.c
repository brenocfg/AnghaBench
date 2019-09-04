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
 double sqrt (double) ; 

double rk_triangular(rk_state *state, double left, double mode, double right)
{
    double base, leftbase, ratio, leftprod, rightprod;
    double U;

    base = right - left;
    leftbase = mode - left;
    ratio = leftbase / base;
    leftprod = leftbase*base;
    rightprod = (right - mode)*base;

    U = rk_double(state);
    if (U <= ratio)
    {
        return left + sqrt(U*leftprod);
    } else
    {
        return right - sqrt((1.0 - U) * rightprod);
    }
}