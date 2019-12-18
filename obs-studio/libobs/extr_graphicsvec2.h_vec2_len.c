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
struct vec2 {int x; int y; } ;

/* Variables and functions */
 float sqrtf (int) ; 

__attribute__((used)) static inline float vec2_len(const struct vec2 *v)
{
	return sqrtf(v->x * v->x + v->y * v->y);
}