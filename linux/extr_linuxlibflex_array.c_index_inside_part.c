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
struct flex_array {unsigned int elems_per_part; unsigned int element_size; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int index_inside_part(struct flex_array *fa,
					unsigned int element_nr,
					unsigned int part_nr)
{
	unsigned int part_offset;

	part_offset = element_nr - part_nr * fa->elems_per_part;
	return part_offset * fa->element_size;
}