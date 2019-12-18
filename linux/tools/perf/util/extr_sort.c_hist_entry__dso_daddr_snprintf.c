#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct map {int dummy; } ;
struct hist_entry {TYPE_2__* mem_info; } ;
struct TYPE_3__ {struct map* map; } ;
struct TYPE_4__ {TYPE_1__ daddr; } ;

/* Variables and functions */
 int _hist_entry__dso_snprintf (struct map*,char*,size_t,unsigned int) ; 

__attribute__((used)) static int hist_entry__dso_daddr_snprintf(struct hist_entry *he, char *bf,
				    size_t size, unsigned int width)
{
	struct map *map = NULL;

	if (he->mem_info)
		map = he->mem_info->daddr.map;

	return _hist_entry__dso_snprintf(map, bf, size, width);
}