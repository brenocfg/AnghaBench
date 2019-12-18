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
struct map {int /*<<< orphan*/  dso; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 struct dso* dso__get (int /*<<< orphan*/ ) ; 
 struct map* dso__new_map (char const*) ; 
 scalar_t__ map__load (struct map*) ; 
 int /*<<< orphan*/  map__put (struct map*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static struct dso *load_dso(const char *name)
{
	struct map *map;
	struct dso *dso;

	map = dso__new_map(name);
	if (!map)
		return NULL;

	if (map__load(map) < 0)
		pr_err("File '%s' not found or has no symbols.\n", name);

	dso = dso__get(map->dso);

	map__put(map);

	return dso;
}