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
struct vec2 {scalar_t__ y; scalar_t__ x; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec2_set (struct vec2*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline void vec2_addf(struct vec2 *dst, const struct vec2 *v, float f)
{
	vec2_set(dst, v->x + f, v->y + f);
}