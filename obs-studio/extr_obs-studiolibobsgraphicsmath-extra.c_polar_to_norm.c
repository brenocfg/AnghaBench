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
struct vec3 {float x; float y; float z; } ;
struct vec2 {int /*<<< orphan*/  x; int /*<<< orphan*/  y; } ;

/* Variables and functions */
 float cosf (int /*<<< orphan*/ ) ; 
 float sinf (int /*<<< orphan*/ ) ; 

void polar_to_norm(struct vec3 *dst, const struct vec2 *polar)
{
	float sinx = sinf(polar->x);

	dst->x = sinx * cosf(polar->y);
	dst->y = sinx * sinf(polar->y);
	dst->z = cosf(polar->x);
}