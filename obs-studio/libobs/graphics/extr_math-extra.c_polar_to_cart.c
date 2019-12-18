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
struct vec3 {float x; float z; float y; } ;

/* Variables and functions */
 float cosf (float) ; 
 float sinf (float) ; 
 int /*<<< orphan*/  vec3_copy (struct vec3*,struct vec3*) ; 

void polar_to_cart(struct vec3 *dst, const struct vec3 *v)
{
	struct vec3 cart;
	float sinx = cosf(v->x);
	float sinx_z = v->z * sinx;

	cart.x = sinx_z * sinf(v->y);
	cart.z = sinx_z * cosf(v->y);
	cart.y = v->z * sinf(v->x);

	vec3_copy(dst, &cart);
}