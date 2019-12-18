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

/* Variables and functions */

__attribute__((used)) static int gdAlphaOverlayColor (int src, int dst, int max )
{
	/* this function implements the algorithm
	 *
	 * for dst[rgb] < 0.5,
	 *   c[rgb] = 2.src[rgb].dst[rgb]
	 * and for dst[rgb] > 0.5,
	 *   c[rgb] = -2.src[rgb].dst[rgb] + 2.dst[rgb] + 2.src[rgb] - 1
	 *
	 */

	dst = dst << 1;
	if( dst > max ) {
		/* in the "light" zone */
		return dst + (src << 1) - (dst * src / max) - max;
	} else {
		/* in the "dark" zone */
		return dst * src / max;
	}
}