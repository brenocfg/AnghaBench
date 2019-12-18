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
typedef  int /*<<< orphan*/  float8 ;

/* Variables and functions */
 scalar_t__ FPge (int /*<<< orphan*/ ,double) ; 
 scalar_t__ FPgt (int /*<<< orphan*/ ,double) ; 
 scalar_t__ FPle (int /*<<< orphan*/ ,double) ; 
 scalar_t__ FPlt (int /*<<< orphan*/ ,double) ; 
 scalar_t__ FPzero (int /*<<< orphan*/ ) ; 
 int POINT_ON_POLYGON ; 
 int /*<<< orphan*/  float8_mi (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  float8_mul (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
lseg_crossing(float8 x, float8 y, float8 prev_x, float8 prev_y)
{
	float8		z;
	int			y_sign;

	if (FPzero(y))
	{							/* y == 0, on X axis */
		if (FPzero(x))			/* (x,y) is (0,0)? */
			return POINT_ON_POLYGON;
		else if (FPgt(x, 0))
		{						/* x > 0 */
			if (FPzero(prev_y)) /* y and prev_y are zero */
				/* prev_x > 0? */
				return FPgt(prev_x, 0.0) ? 0 : POINT_ON_POLYGON;
			return FPlt(prev_y, 0.0) ? 1 : -1;
		}
		else
		{						/* x < 0, x not on positive X axis */
			if (FPzero(prev_y))
				/* prev_x < 0? */
				return FPlt(prev_x, 0.0) ? 0 : POINT_ON_POLYGON;
			return 0;
		}
	}
	else
	{							/* y != 0 */
		/* compute y crossing direction from previous point */
		y_sign = FPgt(y, 0.0) ? 1 : -1;

		if (FPzero(prev_y))
			/* previous point was on X axis, so new point is either off or on */
			return FPlt(prev_x, 0.0) ? 0 : y_sign;
		else if ((y_sign < 0 && FPlt(prev_y, 0.0)) ||
				 (y_sign > 0 && FPgt(prev_y, 0.0)))
			/* both above or below X axis */
			return 0;			/* same sign */
		else
		{						/* y and prev_y cross X-axis */
			if (FPge(x, 0.0) && FPgt(prev_x, 0.0))
				/* both non-negative so cross positive X-axis */
				return 2 * y_sign;
			if (FPlt(x, 0.0) && FPle(prev_x, 0.0))
				/* both non-positive so do not cross positive X-axis */
				return 0;

			/* x and y cross axes, see URL above point_inside() */
			z = float8_mi(float8_mul(float8_mi(x, prev_x), y),
						  float8_mul(float8_mi(y, prev_y), x));
			if (FPzero(z))
				return POINT_ON_POLYGON;
			if ((y_sign < 0 && FPlt(z, 0.0)) ||
				(y_sign > 0 && FPgt(z, 0.0)))
				return 0;
			return 2 * y_sign;
		}
	}
}