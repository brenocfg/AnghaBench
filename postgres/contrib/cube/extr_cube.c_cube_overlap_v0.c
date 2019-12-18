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
 int DIM (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LL_COORD (int /*<<< orphan*/ *,int) ; 
 scalar_t__ Max (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Min (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UR_COORD (int /*<<< orphan*/ *,int) ; 

bool
cube_overlap_v0(NDBOX *a, NDBOX *b)
{
	int			i;

	if ((a == NULL) || (b == NULL))
		return false;

	/* swap the box pointers if needed */
	if (DIM(a) < DIM(b))
	{
		NDBOX	   *tmp = b;

		b = a;
		a = tmp;
	}

	/* compare within the dimensions of (b) */
	for (i = 0; i < DIM(b); i++)
	{
		if (Min(LL_COORD(a, i), UR_COORD(a, i)) > Max(LL_COORD(b, i), UR_COORD(b, i)))
			return false;
		if (Max(LL_COORD(a, i), UR_COORD(a, i)) < Min(LL_COORD(b, i), UR_COORD(b, i)))
			return false;
	}

	/* compare to zero those dimensions in (a) absent in (b) */
	for (i = DIM(b); i < DIM(a); i++)
	{
		if (Min(LL_COORD(a, i), UR_COORD(a, i)) > 0)
			return false;
		if (Max(LL_COORD(a, i), UR_COORD(a, i)) < 0)
			return false;
	}

	return true;
}