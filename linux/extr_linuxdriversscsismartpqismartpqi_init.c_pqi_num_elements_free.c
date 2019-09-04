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

__attribute__((used)) static inline unsigned int pqi_num_elements_free(unsigned int pi,
	unsigned int ci, unsigned int elements_in_queue)
{
	unsigned int num_elements_used;

	if (pi >= ci)
		num_elements_used = pi - ci;
	else
		num_elements_used = elements_in_queue - ci + pi;

	return elements_in_queue - num_elements_used - 1;
}