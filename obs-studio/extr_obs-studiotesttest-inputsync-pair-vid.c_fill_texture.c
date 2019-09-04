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
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline void fill_texture(uint32_t *pixels, uint32_t pixel)
{
	size_t x, y;

	for (y = 0; y < 32; y++) {
		for (x = 0; x < 32; x++) {
			pixels[y*32 + x] = pixel;
		}
	}
}