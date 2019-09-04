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
 long rk_geometric_inversion (int /*<<< orphan*/ *,double) ; 
 long rk_geometric_search (int /*<<< orphan*/ *,double) ; 

long rk_geometric(rk_state *state, double p)
{
    if (p >= 0.333333333333333333333333)
    {
        return rk_geometric_search(state, p);
    } else
    {
        return rk_geometric_inversion(state, p);
    }
}