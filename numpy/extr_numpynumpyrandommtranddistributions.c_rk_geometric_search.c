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

long rk_geometric_search(rk_state *state, double p)
{
    double U;
    long X;
    double sum, prod, q;

    X = 1;
    sum = prod = p;
    q = 1.0 - p;
    U = rk_double(state);
    while (U > sum)
    {
        prod *= q;
        sum += prod;
        X++;
    }
    return X;
}