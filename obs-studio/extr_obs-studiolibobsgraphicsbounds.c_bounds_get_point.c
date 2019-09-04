#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct vec3 {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_3__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_4__ {int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct bounds {TYPE_1__ min; TYPE_2__ max; } ;

/* Variables and functions */

void bounds_get_point(struct vec3 *dst, const struct bounds *b,
		unsigned int i)
{
	if (i > 8)
		return;

	/*
	 * Note:
	 * 0 = min.x,min.y,min.z
	 * 1 = min.x,min.y,MAX.z
	 * 2 = min.x,MAX.y,min.z
	 * 3 = min.x,MAX.y,MAX.z
	 * 4 = MAX.x,min.y,min.z
	 * 5 = MAX.x,min.y,MAX.z

	 * 6 = MAX.x,MAX.y,min.z
	 * 7 = MAX.x,MAX.y,MAX.z
	 */

	if(i > 3)  {dst->x = b->max.x; i -= 4;}
	else       {dst->x = b->min.x;}

	if(i > 1)  {dst->y = b->max.y; i -= 2;}
	else       {dst->y = b->min.y;}

	dst->z = (i == 1) ? b->max.z : b->min.z;
}