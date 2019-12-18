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
struct vec2 {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  ceilf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vec2_set (struct vec2*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void vec2_ceil(struct vec2 *dst, const struct vec2 *v)
{
	vec2_set(dst, ceilf(v->x), ceilf(v->y));
}