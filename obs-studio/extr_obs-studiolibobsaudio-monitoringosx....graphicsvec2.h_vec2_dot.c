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
struct vec2 {float x; float y; } ;

/* Variables and functions */

__attribute__((used)) static inline float vec2_dot(const struct vec2 *v1, const struct vec2 *v2)
{
	return v1->x*v2->x + v1->y*v2->y;
}