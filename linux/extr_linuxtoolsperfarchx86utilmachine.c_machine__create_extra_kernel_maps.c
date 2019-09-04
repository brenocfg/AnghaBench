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
struct machine {int trampolines_mapped; } ;
struct extra_kernel_map_info {int cnt; struct extra_kernel_map* maps; scalar_t__ entry_trampoline; } ;
struct extra_kernel_map {scalar_t__ pgoff; } ;
struct dso {int dummy; } ;

/* Variables and functions */
 int PATH_MAX ; 
 int /*<<< orphan*/  find_extra_kernel_maps ; 
 int /*<<< orphan*/  free (struct extra_kernel_map*) ; 
 int kallsyms__parse (char*,struct extra_kernel_map_info*,int /*<<< orphan*/ ) ; 
 int machine__create_extra_kernel_map (struct machine*,struct dso*,struct extra_kernel_map*) ; 
 int /*<<< orphan*/  machine__get_kallsyms_filename (struct machine*,char*,int) ; 
 scalar_t__ symbol__restricted_filename (char*,char*) ; 

int machine__create_extra_kernel_maps(struct machine *machine,
				      struct dso *kernel)
{
	struct extra_kernel_map_info mi = { .cnt = 0, };
	char filename[PATH_MAX];
	int ret;
	int i;

	machine__get_kallsyms_filename(machine, filename, PATH_MAX);

	if (symbol__restricted_filename(filename, "/proc/kallsyms"))
		return 0;

	ret = kallsyms__parse(filename, &mi, find_extra_kernel_maps);
	if (ret)
		goto out_free;

	if (!mi.entry_trampoline)
		goto out_free;

	for (i = 0; i < mi.cnt; i++) {
		struct extra_kernel_map *xm = &mi.maps[i];

		xm->pgoff = mi.entry_trampoline;
		ret = machine__create_extra_kernel_map(machine, kernel, xm);
		if (ret)
			goto out_free;
	}

	machine->trampolines_mapped = mi.cnt;
out_free:
	free(mi.maps);
	return ret;
}