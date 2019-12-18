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
struct vec4 {void* w; void* z; void* y; void* x; } ;
struct matrix4 {int /*<<< orphan*/  t; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix4_transpose (struct matrix4*,struct matrix4 const*) ; 
 int /*<<< orphan*/  vec4_copy (struct vec4*,struct vec4*) ; 
 void* vec4_dot (int /*<<< orphan*/ *,struct vec4 const*) ; 

void vec4_transform(struct vec4 *dst, const struct vec4 *v,
		    const struct matrix4 *m)
{
	struct vec4 temp;
	struct matrix4 transpose;

	matrix4_transpose(&transpose, m);

	temp.x = vec4_dot(&transpose.x, v);
	temp.y = vec4_dot(&transpose.y, v);
	temp.z = vec4_dot(&transpose.z, v);
	temp.w = vec4_dot(&transpose.t, v);

	vec4_copy(dst, &temp);
}