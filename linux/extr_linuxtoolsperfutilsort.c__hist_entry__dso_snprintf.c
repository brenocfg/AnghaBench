#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct map {TYPE_1__* dso; } ;
struct TYPE_2__ {char* long_name; char* short_name; } ;

/* Variables and functions */
 int repsep_snprintf (char*,size_t,char*,unsigned int,unsigned int,char const*) ; 
 scalar_t__ verbose ; 

__attribute__((used)) static int _hist_entry__dso_snprintf(struct map *map, char *bf,
				     size_t size, unsigned int width)
{
	if (map && map->dso) {
		const char *dso_name = verbose > 0 ? map->dso->long_name :
			map->dso->short_name;
		return repsep_snprintf(bf, size, "%-*.*s", width, width, dso_name);
	}

	return repsep_snprintf(bf, size, "%-*.*s", width, width, "[unknown]");
}