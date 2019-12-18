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
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_3__ {int /*<<< orphan*/  xseed; } ;
typedef  TYPE_1__ RandomState ;

/* Variables and functions */
 double log (double) ; 
 double pg_erand48 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
getPoissonRand(RandomState *random_state, double center)
{
	/*
	 * Use inverse transform sampling to generate a value > 0, such that the
	 * expected (i.e. average) value is the given argument.
	 */
	double		uniform;

	/* erand in [0, 1), uniform in (0, 1] */
	uniform = 1.0 - pg_erand48(random_state->xseed);

	return (int64) (-log(uniform) * center + 0.5);
}