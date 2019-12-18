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
typedef  int /*<<< orphan*/  NDBOX ;

/* Variables and functions */
 double Abs (scalar_t__) ; 
 int DIM (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_POINT (int /*<<< orphan*/ *) ; 
 scalar_t__ LL_COORD (int /*<<< orphan*/ *,int) ; 
 scalar_t__ UR_COORD (int /*<<< orphan*/ *,int) ; 

void
rt_cube_size(NDBOX *a, double *size)
{
	double		result;
	int			i;

	if (a == (NDBOX *) NULL)
	{
		/* special case for GiST */
		result = 0.0;
	}
	else if (IS_POINT(a) || DIM(a) == 0)
	{
		/* necessarily has zero size */
		result = 0.0;
	}
	else
	{
		result = 1.0;
		for (i = 0; i < DIM(a); i++)
			result *= Abs(UR_COORD(a, i) - LL_COORD(a, i));
	}
	*size = result;
}