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
struct vec3 {int /*<<< orphan*/  y; int /*<<< orphan*/  z; int /*<<< orphan*/  x; } ;
struct vec2 {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  asinf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atan2f (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void norm_to_polar(struct vec2 *dst, const struct vec3 *norm)
{
	dst->x = atan2f(norm->x, norm->z);
	dst->y = asinf(norm->y);
}