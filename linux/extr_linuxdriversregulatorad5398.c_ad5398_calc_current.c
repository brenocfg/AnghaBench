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
struct ad5398_chip_info {unsigned int max_uA; unsigned int min_uA; unsigned int current_level; } ;

/* Variables and functions */

__attribute__((used)) static int ad5398_calc_current(struct ad5398_chip_info *chip,
	unsigned selector)
{
	unsigned range_uA = chip->max_uA - chip->min_uA;

	return chip->min_uA + (selector * range_uA / chip->current_level);
}