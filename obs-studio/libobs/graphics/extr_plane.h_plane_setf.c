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
struct plane {float dist; int /*<<< orphan*/  dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec3_set (int /*<<< orphan*/ *,float,float,float) ; 

__attribute__((used)) static inline void plane_setf(struct plane *dst, float a, float b, float c,
			      float d)
{
	vec3_set(&dst->dir, a, b, c);
	dst->dist = d;
}