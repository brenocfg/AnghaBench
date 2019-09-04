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
struct bounds {int /*<<< orphan*/  min; int /*<<< orphan*/  max; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec3_add (struct vec3*,struct vec3*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vec3_mulf (struct vec3*,struct vec3*,float) ; 
 int /*<<< orphan*/  vec3_sub (struct vec3*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void bounds_get_center(struct vec3 *dst, const struct bounds *b)
{
	vec3_sub(dst, &b->max, &b->min);
	vec3_mulf(dst, dst, 0.5f);
	vec3_add(dst, dst, &b->min);
}