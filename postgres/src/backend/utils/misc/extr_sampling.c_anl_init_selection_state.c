#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__* randstate; } ;

/* Variables and functions */
 double exp (int) ; 
 int log (int /*<<< orphan*/ ) ; 
 TYPE_1__ oldrs ; 
 int /*<<< orphan*/  random () ; 
 int /*<<< orphan*/  sampler_random_fract (scalar_t__*) ; 
 int /*<<< orphan*/  sampler_random_init_state (int /*<<< orphan*/ ,scalar_t__*) ; 

double
anl_init_selection_state(int n)
{
	/* initialize if first time through */
	if (oldrs.randstate[0] == 0)
		sampler_random_init_state(random(), oldrs.randstate);

	/* Initial value of W (for use when Algorithm Z is first applied) */
	return exp(-log(sampler_random_fract(oldrs.randstate)) / n);
}