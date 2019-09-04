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
struct vec3 {float w; void* z; void* y; void* x; } ;

/* Variables and functions */
 void* fabsf (void*) ; 

__attribute__((used)) static inline void vec3_abs(struct vec3 *dst, const struct vec3 *v)
{
	dst->x = fabsf(v->x);
	dst->y = fabsf(v->y);
	dst->z = fabsf(v->z);
	dst->w = 0.0f;
}