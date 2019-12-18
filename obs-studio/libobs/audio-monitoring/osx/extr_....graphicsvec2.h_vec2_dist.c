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
struct vec2 {int dummy; } ;

/* Variables and functions */
 float vec2_len (struct vec2*) ; 
 int /*<<< orphan*/  vec2_sub (struct vec2*,struct vec2 const*,struct vec2 const*) ; 

__attribute__((used)) static inline float vec2_dist(const struct vec2 *v1, const struct vec2 *v2)
{
	struct vec2 temp;
	vec2_sub(&temp, v1, v2);
	return vec2_len(&temp);
}