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
 double pow (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rk_standard_exponential (int /*<<< orphan*/ *) ; 

double rk_weibull(rk_state *state, double a)
{
    if (a == 0.0) {
        return 0.0;
    }
    return pow(rk_standard_exponential(state), 1./a);
}