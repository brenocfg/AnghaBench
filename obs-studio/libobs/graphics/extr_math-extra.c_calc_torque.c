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
struct vec3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPSILON ; 
 float LARGE_EPSILON ; 
 int /*<<< orphan*/  vec3_add (struct vec3*,struct vec3*,struct vec3 const*) ; 
 scalar_t__ vec3_close (struct vec3 const*,struct vec3 const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec3_copy (struct vec3*,struct vec3 const*) ; 
 float vec3_len (struct vec3*) ; 
 int /*<<< orphan*/  vec3_mulf (struct vec3*,struct vec3*,float) ; 
 int /*<<< orphan*/  vec3_sub (struct vec3*,struct vec3 const*,struct vec3 const*) ; 

void calc_torque(struct vec3 *dst, const struct vec3 *v1, const struct vec3 *v2,
		 float torque, float min_adjust, float t)
{
	struct vec3 line, dir;
	float orig_dist, torque_dist, adjust_dist;

	if (vec3_close(v1, v2, EPSILON)) {
		vec3_copy(dst, v1);
		return;
	}

	vec3_sub(&line, v2, v1);
	orig_dist = vec3_len(&line);
	vec3_mulf(&dir, &line, 1.0f / orig_dist);

	torque_dist = orig_dist * torque; /* use distance to determine speed */
	if (torque_dist < min_adjust)     /* prevent from going too slow */
		torque_dist = min_adjust;

	adjust_dist = torque_dist * t;

	if (adjust_dist <= (orig_dist - LARGE_EPSILON)) {
		vec3_mulf(dst, &dir, adjust_dist);
		vec3_add(dst, dst, v1); /* add torque */
	} else {
		vec3_copy(dst, v2); /* clamp if overshoot */
	}
}