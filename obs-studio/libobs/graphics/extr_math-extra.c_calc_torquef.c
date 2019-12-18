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

/* Variables and functions */
 int /*<<< orphan*/  EPSILON ; 
 scalar_t__ close_float (float,float,int /*<<< orphan*/ ) ; 

float calc_torquef(float val1, float val2, float torque, float min_adjust,
		   float t)
{
	float out = val1;
	float dist;
	bool over;

	if (close_float(val1, val2, EPSILON))
		return val1;

	dist = (val2 - val1) * torque;
	over = dist > 0.0f;

	if (over) {
		if (dist < min_adjust) /* prevents from going too slow */
			dist = min_adjust;
		out += dist * t; /* add torque */
		if (out > val2)  /* clamp if overshoot */
			out = val2;
	} else {
		if (dist > -min_adjust)
			dist = -min_adjust;
		out += dist * t;
		if (out < val2)
			out = val2;
	}

	return out;
}