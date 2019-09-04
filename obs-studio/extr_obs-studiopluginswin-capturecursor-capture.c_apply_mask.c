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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  bit_to_alpha (int /*<<< orphan*/ *,long,int) ; 

__attribute__((used)) static inline void apply_mask(uint8_t *color, uint8_t *mask, long num_pixels)
{
	for (long i = 0; i < num_pixels; i++)
		color[i * 4 + 3] = bit_to_alpha(mask, i, false);
}