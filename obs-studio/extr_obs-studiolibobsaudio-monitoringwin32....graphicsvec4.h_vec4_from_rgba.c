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
typedef  int uint32_t ;
struct vec4 {float x; float y; float z; float w; } ;

/* Variables and functions */

__attribute__((used)) static inline void vec4_from_rgba(struct vec4 *dst, uint32_t rgba)
{
	dst->x = (float)((double)(rgba&0xFF) * (1.0/255.0));
	rgba >>= 8;
	dst->y = (float)((double)(rgba&0xFF) * (1.0/255.0));
	rgba >>= 8;
	dst->z = (float)((double)(rgba&0xFF) * (1.0/255.0));
	rgba >>= 8;
	dst->w = (float)((double)(rgba&0xFF) * (1.0/255.0));
}