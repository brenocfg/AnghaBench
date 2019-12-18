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
struct map {TYPE_1__* groups; } ;
struct machine {char* root_dir; int /*<<< orphan*/  mmap_name; } ;
struct dso {int /*<<< orphan*/  binary_type; } ;
struct TYPE_4__ {char* default_guest_kallsyms; int /*<<< orphan*/ * default_guest_vmlinux_name; } ;
struct TYPE_3__ {struct machine* machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_BINARY_TYPE__GUEST_KALLSYMS ; 
 int PATH_MAX ; 
 int /*<<< orphan*/  dso__is_kcore (struct dso*) ; 
 int dso__load_kallsyms (struct dso*,char const*,struct map*) ; 
 int dso__load_vmlinux (struct dso*,struct map*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dso__set_long_name (struct dso*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ machine__is_default_guest (struct machine*) ; 
 int /*<<< orphan*/  map__fixup_end (struct map*) ; 
 int /*<<< orphan*/  map__fixup_start (struct map*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 TYPE_2__ symbol_conf ; 

__attribute__((used)) static int dso__load_guest_kernel_sym(struct dso *dso, struct map *map)
{
	int err;
	const char *kallsyms_filename = NULL;
	struct machine *machine;
	char path[PATH_MAX];

	if (!map->groups) {
		pr_debug("Guest kernel map hasn't the point to groups\n");
		return -1;
	}
	machine = map->groups->machine;

	if (machine__is_default_guest(machine)) {
		/*
		 * if the user specified a vmlinux filename, use it and only
		 * it, reporting errors to the user if it cannot be used.
		 * Or use file guest_kallsyms inputted by user on commandline
		 */
		if (symbol_conf.default_guest_vmlinux_name != NULL) {
			err = dso__load_vmlinux(dso, map,
						symbol_conf.default_guest_vmlinux_name,
						false);
			return err;
		}

		kallsyms_filename = symbol_conf.default_guest_kallsyms;
		if (!kallsyms_filename)
			return -1;
	} else {
		sprintf(path, "%s/proc/kallsyms", machine->root_dir);
		kallsyms_filename = path;
	}

	err = dso__load_kallsyms(dso, kallsyms_filename, map);
	if (err > 0)
		pr_debug("Using %s for symbols\n", kallsyms_filename);
	if (err > 0 && !dso__is_kcore(dso)) {
		dso->binary_type = DSO_BINARY_TYPE__GUEST_KALLSYMS;
		dso__set_long_name(dso, machine->mmap_name, false);
		map__fixup_start(map);
		map__fixup_end(map);
	}

	return err;
}