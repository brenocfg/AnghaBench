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
struct nsinfo {int dummy; } ;
struct map {TYPE_1__* dso; } ;
struct TYPE_2__ {int /*<<< orphan*/  nsinfo; } ;

/* Variables and functions */
 struct map* dso__new_map (char const*) ; 
 struct map* kernel_get_module_map (char const*) ; 
 int /*<<< orphan*/  nsinfo__get (struct nsinfo*) ; 

struct map *get_target_map(const char *target, struct nsinfo *nsi, bool user)
{
	/* Init maps of given executable or kernel */
	if (user) {
		struct map *map;

		map = dso__new_map(target);
		if (map && map->dso)
			map->dso->nsinfo = nsinfo__get(nsi);
		return map;
	} else {
		return kernel_get_module_map(target);
	}
}