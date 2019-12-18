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
struct vec2 {int x; int y; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec2_set (struct vec2*,int,int) ; 

__attribute__((used)) static inline void vec2_div(struct vec2 *dst, const struct vec2 *v1,
			    const struct vec2 *v2)
{
	vec2_set(dst, v1->x / v2->x, v1->y / v2->y);
}