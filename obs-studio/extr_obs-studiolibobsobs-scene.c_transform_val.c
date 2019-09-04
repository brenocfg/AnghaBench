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
struct vec3 {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct vec2 {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct matrix4 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec3_set (struct vec3*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,float) ; 
 int /*<<< orphan*/  vec3_transform (struct vec3*,struct vec3*,struct matrix4*) ; 

__attribute__((used)) static inline void transform_val(struct vec2 *v2, struct matrix4 *transform)
{
	struct vec3 v;
	vec3_set(&v, v2->x, v2->y, 0.0f);
	vec3_transform(&v, &v, transform);
	v2->x = v.x;
	v2->y = v.y;
}