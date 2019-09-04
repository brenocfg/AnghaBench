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
struct resource_map {unsigned long base; int num; struct resource_map* next; } ;
struct resource {unsigned long start; unsigned long end; } ;
struct pcmcia_align_data {struct resource_map* map; } ;
typedef  unsigned long resource_size_t ;

/* Variables and functions */
 unsigned long pcmcia_common_align (struct pcmcia_align_data*,unsigned long) ; 

__attribute__((used)) static resource_size_t
pcmcia_align(void *align_data, const struct resource *res,
	resource_size_t size, resource_size_t align)
{
	struct pcmcia_align_data *data = align_data;
	struct resource_map *m;
	resource_size_t start;

	start = pcmcia_common_align(data, res->start);

	for (m = data->map->next; m != data->map; m = m->next) {
		unsigned long map_start = m->base;
		unsigned long map_end = m->base + m->num - 1;

		/*
		 * If the lower resources are not available, try aligning
		 * to this entry of the resource database to see if it'll
		 * fit here.
		 */
		if (start < map_start)
			start = pcmcia_common_align(data, map_start);

		/*
		 * If we're above the area which was passed in, there's
		 * no point proceeding.
		 */
		if (start >= res->end)
			break;

		if ((start + size - 1) <= map_end)
			break;
	}

	/*
	 * If we failed to find something suitable, ensure we fail.
	 */
	if (m == data->map)
		start = res->end;

	return start;
}