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
 long rk_poisson_mult (int /*<<< orphan*/ *,double) ; 
 long rk_poisson_ptrs (int /*<<< orphan*/ *,double) ; 

long rk_poisson(rk_state *state, double lam)
{
    if (lam >= 10)
    {
        return rk_poisson_ptrs(state, lam);
    }
    else if (lam == 0)
    {
        return 0;
    }
    else
    {
        return rk_poisson_mult(state, lam);
    }
}