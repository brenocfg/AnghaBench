#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {float x; float y; float z; } ;
struct matrix3 {TYPE_1__ z; TYPE_1__ y; TYPE_1__ x; TYPE_1__ t; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec3_zero (TYPE_1__*) ; 

__attribute__((used)) static inline void matrix3_identity(struct matrix3 *dst)
{
	vec3_zero(&dst->x);
	vec3_zero(&dst->y);
	vec3_zero(&dst->z);
	vec3_zero(&dst->t);
	dst->x.x = dst->y.y = dst->z.z = 1.0f;
}