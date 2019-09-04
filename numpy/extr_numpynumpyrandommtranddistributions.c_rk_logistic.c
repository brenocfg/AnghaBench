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
 double log (double) ; 
 double rk_double (int /*<<< orphan*/ *) ; 

double rk_logistic(rk_state *state, double loc, double scale)
{
    double U;

    U = rk_double(state);
    return loc + scale * log(U/(1.0 - U));
}