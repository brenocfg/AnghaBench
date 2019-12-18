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
struct maps {int dummy; } ;
struct map {TYPE_1__* dso; } ;
struct TYPE_2__ {int short_name_len; scalar_t__ short_name; } ;

/* Variables and functions */
 struct map* dso__new_map (char const*) ; 
 int /*<<< orphan*/  host_machine ; 
 struct map* machine__kernel_map (int /*<<< orphan*/ ) ; 
 struct maps* machine__kernel_maps (int /*<<< orphan*/ ) ; 
 struct map* map__get (struct map*) ; 
 struct map* map__next (struct map*) ; 
 struct map* maps__first (struct maps*) ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strncmp (scalar_t__,char const*,int) ; 

__attribute__((used)) static struct map *kernel_get_module_map(const char *module)
{
	struct maps *maps = machine__kernel_maps(host_machine);
	struct map *pos;

	/* A file path -- this is an offline module */
	if (module && strchr(module, '/'))
		return dso__new_map(module);

	if (!module) {
		pos = machine__kernel_map(host_machine);
		return map__get(pos);
	}

	for (pos = maps__first(maps); pos; pos = map__next(pos)) {
		/* short_name is "[module]" */
		if (strncmp(pos->dso->short_name + 1, module,
			    pos->dso->short_name_len - 2) == 0 &&
		    module[pos->dso->short_name_len - 2] == '\0') {
			return map__get(pos);
		}
	}
	return NULL;
}