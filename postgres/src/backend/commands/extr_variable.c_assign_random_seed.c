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

/* Variables and functions */
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Float8GetDatum (double) ; 
 int /*<<< orphan*/  setseed ; 

void
assign_random_seed(double newval, void *extra)
{
	/* We'll do this at most once for any setting of the GUC variable */
	if (*((int *) extra))
		DirectFunctionCall1(setseed, Float8GetDatum(newval));
	*((int *) extra) = 0;
}