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
struct vec4 {int dummy; } ;
struct matrix4 {int /*<<< orphan*/  t; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix4_mul (struct matrix4*,struct matrix4 const*,struct matrix4*) ; 
 int /*<<< orphan*/  vec4_copy (int /*<<< orphan*/ *,struct vec4 const*) ; 
 int /*<<< orphan*/  vec4_set (int /*<<< orphan*/ *,float,float,float,float) ; 

void matrix4_translate4v(struct matrix4 *dst, const struct matrix4 *m,
			 const struct vec4 *v)
{
	struct matrix4 temp;
	vec4_set(&temp.x, 1.0f, 0.0f, 0.0f, 0.0f);
	vec4_set(&temp.y, 0.0f, 1.0f, 0.0f, 0.0f);
	vec4_set(&temp.z, 0.0f, 0.0f, 1.0f, 0.0f);
	vec4_copy(&temp.t, v);

	matrix4_mul(dst, m, &temp);
}