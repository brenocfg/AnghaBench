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
struct bounds {int /*<<< orphan*/  max; int /*<<< orphan*/  min; } ;

/* Variables and functions */
 int /*<<< orphan*/  vec3_zero (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void bounds_zero(struct bounds *dst)
{
	vec3_zero(&dst->min);
	vec3_zero(&dst->max);
}