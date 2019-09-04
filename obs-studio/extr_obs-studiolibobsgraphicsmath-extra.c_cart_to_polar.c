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
struct vec3 {int z; int y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  EPSILON ; 
 int /*<<< orphan*/  asinf (int) ; 
 int atan2f (int /*<<< orphan*/ ,int) ; 
 scalar_t__ close_float (int,float,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec3_copy (struct vec3*,struct vec3*) ; 
 int vec3_len (struct vec3 const*) ; 
 int /*<<< orphan*/  vec3_zero (struct vec3*) ; 

void cart_to_polar(struct vec3 *dst, const struct vec3 *v)
{
	struct vec3 polar;
	polar.z = vec3_len(v);

	if (close_float(polar.z, 0.0f, EPSILON)) {
		vec3_zero(&polar);
	} else {
		polar.x = asinf(v->y / polar.z);
		polar.y = atan2f(v->x, v->z);
	}

	vec3_copy(dst, &polar);
}