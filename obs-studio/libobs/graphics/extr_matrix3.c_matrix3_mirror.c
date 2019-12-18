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
struct plane {int /*<<< orphan*/  dir; } ;
struct matrix3 {int /*<<< orphan*/  t; int /*<<< orphan*/  z; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec3_mirror (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct plane const*) ; 
 int /*<<< orphan*/  vec3_mirrorv (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void matrix3_mirror(struct matrix3 *dst, const struct matrix3 *m,
		    const struct plane *p)
{
	vec3_mirrorv(&dst->x, &m->x, &p->dir);
	vec3_mirrorv(&dst->y, &m->y, &p->dir);
	vec3_mirrorv(&dst->z, &m->z, &p->dir);
	vec3_mirror(&dst->t, &m->t, p);
}