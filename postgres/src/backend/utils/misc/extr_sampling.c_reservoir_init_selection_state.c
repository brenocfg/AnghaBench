#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  randstate; int /*<<< orphan*/  W; } ;
typedef  TYPE_1__* ReservoirState ;

/* Variables and functions */
 int /*<<< orphan*/  exp (int) ; 
 int log (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  random () ; 
 int /*<<< orphan*/  sampler_random_fract (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sampler_random_init_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
reservoir_init_selection_state(ReservoirState rs, int n)
{
	/*
	 * Reservoir sampling is not used anywhere where it would need to return
	 * repeatable results so we can initialize it randomly.
	 */
	sampler_random_init_state(random(), rs->randstate);

	/* Initial value of W (for use when Algorithm Z is first applied) */
	rs->W = exp(-log(sampler_random_fract(rs->randstate)) / n);
}