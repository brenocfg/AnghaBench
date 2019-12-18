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
typedef  int /*<<< orphan*/  u64 ;
struct map {int /*<<< orphan*/  dso; } ;
struct machine {int /*<<< orphan*/  kmaps; } ;
struct kmod_path {int /*<<< orphan*/  name; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dso__adjust_kmod_long_name (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  dso__put (struct dso*) ; 
 scalar_t__ kmod_path__parse_name (struct kmod_path*,char const*) ; 
 struct dso* machine__findnew_module_dso (struct machine*,struct kmod_path*,char const*) ; 
 struct map* map__new2 (int /*<<< orphan*/ ,struct dso*) ; 
 int /*<<< orphan*/  map__put (struct map*) ; 
 struct map* map_groups__find_by_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  map_groups__insert (int /*<<< orphan*/ *,struct map*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *) ; 

struct map *machine__findnew_module_map(struct machine *machine, u64 start,
					const char *filename)
{
	struct map *map = NULL;
	struct dso *dso = NULL;
	struct kmod_path m;

	if (kmod_path__parse_name(&m, filename))
		return NULL;

	map = map_groups__find_by_name(&machine->kmaps, m.name);
	if (map) {
		/*
		 * If the map's dso is an offline module, give dso__load()
		 * a chance to find the file path of that module by fixing
		 * long_name.
		 */
		dso__adjust_kmod_long_name(map->dso, filename);
		goto out;
	}

	dso = machine__findnew_module_dso(machine, &m, filename);
	if (dso == NULL)
		goto out;

	map = map__new2(start, dso);
	if (map == NULL)
		goto out;

	map_groups__insert(&machine->kmaps, map);

	/* Put the map here because map_groups__insert alread got it */
	map__put(map);
out:
	/* put the dso here, corresponding to  machine__findnew_module_dso */
	dso__put(dso);
	zfree(&m.name);
	return map;
}