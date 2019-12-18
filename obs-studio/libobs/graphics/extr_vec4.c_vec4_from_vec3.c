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
struct vec4 {float w; int /*<<< orphan*/  m; } ;
struct vec3 {int /*<<< orphan*/  m; } ;

/* Variables and functions */

void vec4_from_vec3(struct vec4 *dst, const struct vec3 *v)
{
	dst->m = v->m;
	dst->w = 1.0f;
}