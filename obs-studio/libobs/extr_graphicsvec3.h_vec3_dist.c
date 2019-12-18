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
 float sqrtf (float) ; 
 float vec3_dot (struct vec3*,struct vec3*) ; 
 int /*<<< orphan*/  vec3_sub (struct vec3*,struct vec3 const*,struct vec3 const*) ; 

__attribute__((used)) static inline float vec3_dist(const struct vec3 *v1, const struct vec3 *v2)
{
	struct vec3 temp;
	float dot_val;

	vec3_sub(&temp, v1, v2);
	dot_val = vec3_dot(&temp, &temp);
	return (dot_val > 0.0f) ? sqrtf(dot_val) : 0.0f;
}