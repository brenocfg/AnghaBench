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
 double MIN_GAUSSIAN_PARAM ; 
 double M_PI ; 
 double log (double) ; 
 double pg_erand48 (int /*<<< orphan*/ ) ; 
 double sin (double) ; 
 double sqrt (double) ; 

__attribute__((used)) static int64
getGaussianRand(RandomState *random_state, int64 min, int64 max,
				double parameter)
{
	double		stdev;
	double		rand;

	/* abort if parameter is too low, but must really be checked beforehand */
	Assert(parameter >= MIN_GAUSSIAN_PARAM);

	/*
	 * Get user specified random number from this loop, with -parameter <
	 * stdev <= parameter
	 *
	 * This loop is executed until the number is in the expected range.
	 *
	 * As the minimum parameter is 2.0, the probability of looping is low:
	 * sqrt(-2 ln(r)) <= 2 => r >= e^{-2} ~ 0.135, then when taking the
	 * average sinus multiplier as 2/pi, we have a 8.6% looping probability in
	 * the worst case. For a parameter value of 5.0, the looping probability
	 * is about e^{-5} * 2 / pi ~ 0.43%.
	 */
	do
	{
		/*
		 * pg_erand48 generates [0,1), but for the basic version of the
		 * Box-Muller transform the two uniformly distributed random numbers
		 * are expected in (0, 1] (see
		 * https://en.wikipedia.org/wiki/Box-Muller_transform)
		 */
		double		rand1 = 1.0 - pg_erand48(random_state->xseed);
		double		rand2 = 1.0 - pg_erand48(random_state->xseed);

		/* Box-Muller basic form transform */
		double		var_sqrt = sqrt(-2.0 * log(rand1));

		stdev = var_sqrt * sin(2.0 * M_PI * rand2);

		/*
		 * we may try with cos, but there may be a bias induced if the
		 * previous value fails the test. To be on the safe side, let us try
		 * over.
		 */
	}
	while (stdev < -parameter || stdev >= parameter);

	/* stdev is in [-parameter, parameter), normalization to [0,1) */
	rand = (stdev + parameter) / (parameter * 2.0);

	/* return int64 random number within between min and max */
	return min + (int64) ((max - min + 1) * rand);
}