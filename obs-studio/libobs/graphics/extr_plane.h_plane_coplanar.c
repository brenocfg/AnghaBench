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
struct plane {float dist; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int close_float (float,float,float) ; 
 float vec3_dot (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline bool plane_coplanar(const struct plane *p1,
				  const struct plane *p2, float precision)
{
	float cos_angle = vec3_dot(&p1->dir, &p2->dir);

	if (close_float(cos_angle, 1.0f, precision))
		return close_float(p1->dist, p2->dist, precision);
	else if (close_float(cos_angle, -1.0f, precision))
		return close_float(-p1->dist, p2->dist, precision);

	return false;
}