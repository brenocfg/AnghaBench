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
struct vec4 {float x; float y; float z; float w; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec4_sub (struct vec4*,struct vec4 const*,struct vec4 const*) ; 

__attribute__((used)) static inline int vec4_close(const struct vec4 *v1, const struct vec4 *v2,
			     float epsilon)
{
	struct vec4 test;
	vec4_sub(&test, v1, v2);
	return test.x < epsilon && test.y < epsilon && test.z < epsilon &&
	       test.w < epsilon;
}