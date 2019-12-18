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
 int /*<<< orphan*/  vec3_abs (struct vec3*,struct vec3 const*) ; 
 float vec3_dot (struct vec3*,struct vec3*) ; 
 int /*<<< orphan*/  vec3_sub (struct vec3*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline float vec3or_offset_len(const struct bounds *b,
				      const struct vec3 *v)
{
	struct vec3 temp1, temp2;
	vec3_sub(&temp1, &b->max, &b->min);
	vec3_abs(&temp2, v);
	return vec3_dot(&temp1, &temp2);
}