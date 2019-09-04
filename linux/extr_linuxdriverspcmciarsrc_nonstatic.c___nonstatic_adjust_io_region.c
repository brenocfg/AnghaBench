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
struct socket_data {struct resource_map io_db; } ;
struct pcmcia_socket {struct socket_data* resource_data; } ;

/* Variables and functions */
 int ENOMEM ; 

__attribute__((used)) static int __nonstatic_adjust_io_region(struct pcmcia_socket *s,
					unsigned long r_start,
					unsigned long r_end)
{
	struct resource_map *m;
	struct socket_data *s_data = s->resource_data;
	int ret = -ENOMEM;

	for (m = s_data->io_db.next; m != &s_data->io_db; m = m->next) {
		unsigned long start = m->base;
		unsigned long end = m->base + m->num - 1;

		if (start > r_start || r_end > end)
			continue;

		ret = 0;
	}

	return ret;
}