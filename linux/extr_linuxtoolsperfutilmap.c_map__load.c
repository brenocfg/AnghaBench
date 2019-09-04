#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct map {TYPE_1__* dso; } ;
struct TYPE_3__ {char* long_name; int /*<<< orphan*/  build_id; scalar_t__ has_build_id; } ;

/* Variables and functions */
 int SBUILD_ID_SIZE ; 
 int /*<<< orphan*/  build_id__sprintf (int /*<<< orphan*/ ,int,char*) ; 
 int dso__load (TYPE_1__*,struct map*) ; 
 scalar_t__ dso__loaded (TYPE_1__*) ; 
 int /*<<< orphan*/  pr_warning (char*,...) ; 

int map__load(struct map *map)
{
	const char *name = map->dso->long_name;
	int nr;

	if (dso__loaded(map->dso))
		return 0;

	nr = dso__load(map->dso, map);
	if (nr < 0) {
		if (map->dso->has_build_id) {
			char sbuild_id[SBUILD_ID_SIZE];

			build_id__sprintf(map->dso->build_id,
					  sizeof(map->dso->build_id),
					  sbuild_id);
			pr_warning("%s with build id %s not found",
				   name, sbuild_id);
		} else
			pr_warning("Failed to open %s", name);

		pr_warning(", continuing without symbols\n");
		return -1;
	} else if (nr == 0) {
#ifdef HAVE_LIBELF_SUPPORT
		const size_t len = strlen(name);
		const size_t real_len = len - sizeof(DSO__DELETED);

		if (len > sizeof(DSO__DELETED) &&
		    strcmp(name + real_len + 1, DSO__DELETED) == 0) {
			pr_warning("%.*s was updated (is prelink enabled?). "
				"Restart the long running apps that use it!\n",
				   (int)real_len, name);
		} else {
			pr_warning("no symbols found in %s, maybe install "
				   "a debug package?\n", name);
		}
#endif
		return -1;
	}

	return 0;
}