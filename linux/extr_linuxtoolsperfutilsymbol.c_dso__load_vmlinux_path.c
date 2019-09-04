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
struct map {int dummy; } ;
struct dso {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  ignore_vmlinux_buildid; } ;

/* Variables and functions */
 char* dso__build_id_filename (struct dso*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int dso__load_vmlinux (struct dso*,struct map*,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 TYPE_1__ symbol_conf ; 
 char** vmlinux_path ; 
 int vmlinux_path__nr_entries ; 

int dso__load_vmlinux_path(struct dso *dso, struct map *map)
{
	int i, err = 0;
	char *filename = NULL;

	pr_debug("Looking at the vmlinux_path (%d entries long)\n",
		 vmlinux_path__nr_entries + 1);

	for (i = 0; i < vmlinux_path__nr_entries; ++i) {
		err = dso__load_vmlinux(dso, map, vmlinux_path[i], false);
		if (err > 0)
			goto out;
	}

	if (!symbol_conf.ignore_vmlinux_buildid)
		filename = dso__build_id_filename(dso, NULL, 0, false);
	if (filename != NULL) {
		err = dso__load_vmlinux(dso, map, filename, true);
		if (err > 0)
			goto out;
		free(filename);
	}
out:
	return err;
}