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
struct map {scalar_t__ dso; } ;

/* Variables and functions */
 char* map__size (struct map*) ; 
 int repsep_snprintf (char*,size_t,char*,unsigned int,char*) ; 

__attribute__((used)) static int _hist_entry__dso_size_snprintf(struct map *map, char *bf,
					  size_t bf_size, unsigned int width)
{
	if (map && map->dso)
		return repsep_snprintf(bf, bf_size, "%*d", width,
				       map__size(map));

	return repsep_snprintf(bf, bf_size, "%*s", width, "unknown");
}