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
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

__attribute__((used)) static inline uint32_t gs_get_total_levels(uint32_t width, uint32_t height)
{
	uint32_t size = width > height ? width : height;
	uint32_t num_levels = 0;

	while (size > 1) {
		size /= 2;
		num_levels++;
	}

	return num_levels;
}