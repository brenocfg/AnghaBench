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
struct vec3 {float x; float y; float z; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec3_sub (struct vec3*,struct vec3 const*,struct vec3 const*) ; 

__attribute__((used)) static inline bool vec3_close(const struct vec3 *v1, const struct vec3 *v2,
			      float epsilon)
{
	struct vec3 test;
	vec3_sub(&test, v1, v2);
	return test.x < epsilon && test.y < epsilon && test.z < epsilon;
}