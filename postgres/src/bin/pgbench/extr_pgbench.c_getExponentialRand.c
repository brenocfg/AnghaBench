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
typedef  int int64 ;
struct TYPE_3__ {int /*<<< orphan*/  xseed; } ;
typedef  TYPE_1__ RandomState ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 double exp (double) ; 
 double log (double) ; 
 double pg_erand48 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int64
getExponentialRand(RandomState *random_state, int64 min, int64 max,
				   double parameter)
{
	double		cut,
				uniform,
				rand;

	/* abort if wrong parameter, but must really be checked beforehand */
	Assert(parameter > 0.0);
	cut = exp(-parameter);
	/* erand in [0, 1), uniform in (0, 1] */
	uniform = 1.0 - pg_erand48(random_state->xseed);

	/*
	 * inner expression in (cut, 1] (if parameter > 0), rand in [0, 1)
	 */
	Assert((1.0 - cut) != 0.0);
	rand = -log(cut + (1.0 - cut) * uniform) / parameter;
	/* return int64 random number within between min and max */
	return min + (int64) ((max - min + 1) * rand);
}