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
 long rk_hypergeometric_hrua (int /*<<< orphan*/ *,long,long,long) ; 
 long rk_hypergeometric_hyp (int /*<<< orphan*/ *,long,long,long) ; 

long rk_hypergeometric(rk_state *state, long good, long bad, long sample)
{
    if (sample > 10)
    {
        return rk_hypergeometric_hrua(state, good, bad, sample);
    } else
    {
        return rk_hypergeometric_hyp(state, good, bad, sample);
    }
}