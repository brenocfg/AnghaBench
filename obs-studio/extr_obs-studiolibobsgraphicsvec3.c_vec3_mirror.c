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
struct plane {int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec3_mulf (struct vec3*,int /*<<< orphan*/ *,float) ; 
 float vec3_plane_dist (struct vec3 const*,struct plane const*) ; 
 int /*<<< orphan*/  vec3_sub (struct vec3*,struct vec3 const*,struct vec3*) ; 

void vec3_mirror(struct vec3 *dst, const struct vec3 *v, const struct plane *p)
{
	struct vec3 temp;
	vec3_mulf(&temp, &p->dir, vec3_plane_dist(v, p) * 2.0f);
	vec3_sub(dst, v, &temp);
}