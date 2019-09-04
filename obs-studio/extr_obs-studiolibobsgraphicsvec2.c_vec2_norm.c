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
 float vec2_len (struct vec2 const*) ; 
 int /*<<< orphan*/  vec2_mulf (struct vec2*,struct vec2 const*,float) ; 

void vec2_norm(struct vec2 *dst, const struct vec2 *v)
{
	float len = vec2_len(v);

	if (len > 0.0f) {
		len = 1.0f / len;
		vec2_mulf(dst, v, len);
	}
}