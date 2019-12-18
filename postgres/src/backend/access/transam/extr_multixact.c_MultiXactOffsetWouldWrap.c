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
typedef  scalar_t__ uint32 ;
typedef  scalar_t__ MultiXactOffset ;

/* Variables and functions */

__attribute__((used)) static bool
MultiXactOffsetWouldWrap(MultiXactOffset boundary, MultiXactOffset start,
						 uint32 distance)
{
	MultiXactOffset finish;

	/*
	 * Note that offset number 0 is not used (see GetMultiXactIdMembers), so
	 * if the addition wraps around the UINT_MAX boundary, skip that value.
	 */
	finish = start + distance;
	if (finish < start)
		finish++;

	/*-----------------------------------------------------------------------
	 * When the boundary is numerically greater than the starting point, any
	 * value numerically between the two is not wrapped:
	 *
	 *	<----S----B---->
	 *	[---)			 = F wrapped past B (and UINT_MAX)
	 *		 [---)		 = F not wrapped
	 *			  [----] = F wrapped past B
	 *
	 * When the boundary is numerically less than the starting point (i.e. the
	 * UINT_MAX wraparound occurs somewhere in between) then all values in
	 * between are wrapped:
	 *
	 *	<----B----S---->
	 *	[---)			 = F not wrapped past B (but wrapped past UINT_MAX)
	 *		 [---)		 = F wrapped past B (and UINT_MAX)
	 *			  [----] = F not wrapped
	 *-----------------------------------------------------------------------
	 */
	if (start < boundary)
		return finish >= boundary || finish < start;
	else
		return finish >= boundary && finish < start;
}