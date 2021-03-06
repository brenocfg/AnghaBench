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
struct matrix3 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  matrix3_translate (struct matrix3*,struct matrix3 const*,struct vec3*) ; 
 int /*<<< orphan*/  vec3_set (struct vec3*,float,float,float) ; 

__attribute__((used)) static inline void matrix3_translate3f(struct matrix3 *dst,
				       const struct matrix3 *m, float x,
				       float y, float z)
{
	struct vec3 v;
	vec3_set(&v, x, y, z);
	matrix3_translate(dst, m, &v);
}