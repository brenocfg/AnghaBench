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
struct symbol {int dummy; } ;
struct map {int /*<<< orphan*/  dso; } ;

/* Variables and functions */
 struct symbol* dso__find_symbol_by_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dso__sort_by_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dso__sorted_by_name (int /*<<< orphan*/ ) ; 
 scalar_t__ map__load (struct map*) ; 

struct symbol *map__find_symbol_by_name(struct map *map, const char *name)
{
	if (map__load(map) < 0)
		return NULL;

	if (!dso__sorted_by_name(map->dso))
		dso__sort_by_name(map->dso);

	return dso__find_symbol_by_name(map->dso, name);
}