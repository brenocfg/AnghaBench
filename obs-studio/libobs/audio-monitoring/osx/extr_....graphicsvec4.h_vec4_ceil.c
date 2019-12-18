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

/* Variables and functions */
 void* ceilf (void*) ; 

__attribute__((used)) static inline void vec4_ceil(struct vec4 *dst, const struct vec4 *v)
{
	dst->x = ceilf(v->x);
	dst->y = ceilf(v->y);
	dst->z = ceilf(v->z);
	dst->w = ceilf(v->w);
}