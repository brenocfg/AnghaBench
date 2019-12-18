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
typedef  struct matrix3 {int /*<<< orphan*/  t; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } const matrix3 ;

/* Variables and functions */
 int /*<<< orphan*/  matrix3_copy (struct matrix3 const*,struct matrix3 const*) ; 
 int /*<<< orphan*/  vec3_rotate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct matrix3 const*) ; 
 int /*<<< orphan*/  vec3_transform3x4 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct matrix3 const*) ; 

void matrix3_mul(struct matrix3 *dst, const struct matrix3 *m1,
		 const struct matrix3 *m2)
{
	if (dst == m2) {
		struct matrix3 temp;
		vec3_rotate(&temp.x, &m1->x, m2);
		vec3_rotate(&temp.y, &m1->y, m2);
		vec3_rotate(&temp.z, &m1->z, m2);
		vec3_transform3x4(&temp.t, &m1->t, m2);
		matrix3_copy(dst, &temp);
	} else {
		vec3_rotate(&dst->x, &m1->x, m2);
		vec3_rotate(&dst->y, &m1->y, m2);
		vec3_rotate(&dst->z, &m1->z, m2);
		vec3_transform3x4(&dst->t, &m1->t, m2);
	}
}