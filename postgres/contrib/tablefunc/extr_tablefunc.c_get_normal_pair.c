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
typedef  double float8 ;

/* Variables and functions */
 scalar_t__ MAX_RANDOM_VALUE ; 
 double log (double) ; 
 scalar_t__ random () ; 
 double sqrt (double) ; 

__attribute__((used)) static void
get_normal_pair(float8 *x1, float8 *x2)
{
	float8		u1,
				u2,
				v1,
				v2,
				s;

	do
	{
		u1 = (float8) random() / (float8) MAX_RANDOM_VALUE;
		u2 = (float8) random() / (float8) MAX_RANDOM_VALUE;

		v1 = (2.0 * u1) - 1.0;
		v2 = (2.0 * u2) - 1.0;

		s = v1 * v1 + v2 * v2;
	} while (s >= 1.0);

	if (s == 0)
	{
		*x1 = 0;
		*x2 = 0;
	}
	else
	{
		s = sqrt((-2.0 * log(s)) / s);
		*x1 = v1 * s;
		*x2 = v2 * s;
	}
}