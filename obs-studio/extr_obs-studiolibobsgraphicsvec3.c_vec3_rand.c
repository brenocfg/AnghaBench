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
struct vec3 {float w; void* z; void* y; void* x; } ;

/* Variables and functions */
 void* rand_float (int) ; 

void vec3_rand(struct vec3 *dst, int positive_only)
{
	dst->x = rand_float(positive_only);
	dst->y = rand_float(positive_only);
	dst->z = rand_float(positive_only);
	dst->w = 0.0f;
}