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
struct vec2 {scalar_t__ x; scalar_t__ y; } ;

/* Variables and functions */

__attribute__((used)) static inline void vec2_min(struct vec2 *dst, const struct vec2 *v,
		const struct vec2 *min_v)
{
	if (v->x < min_v->x)
		dst->x = min_v->x;
	if (v->y < min_v->y)
		dst->y = min_v->y;
}