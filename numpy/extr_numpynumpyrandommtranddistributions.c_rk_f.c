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

double rk_f(rk_state *state, double dfnum, double dfden)
{
    return ((rk_chisquare(state, dfnum) * dfden) /
            (rk_chisquare(state, dfden) * dfnum));
}