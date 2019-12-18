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
struct dso {int /*<<< orphan*/  binary_type; } ;
struct TYPE_2__ {char* kallsyms_name; scalar_t__* symfs; int /*<<< orphan*/  ignore_vmlinux; int /*<<< orphan*/ * vmlinux_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  DSO_BINARY_TYPE__KALLSYMS ; 
 int /*<<< orphan*/  DSO__NAME_KALLSYMS ; 
 char* dso__find_kallsyms (struct dso*,struct map*) ; 
 int /*<<< orphan*/  dso__is_kcore (struct dso*) ; 
 int dso__load_kallsyms (struct dso*,char const*,struct map*) ; 
 int dso__load_vmlinux (struct dso*,struct map*,int /*<<< orphan*/ *,int) ; 
 int dso__load_vmlinux_path (struct dso*,struct map*) ; 
 int /*<<< orphan*/  dso__set_long_name (struct dso*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  map__fixup_end (struct map*) ; 
 int /*<<< orphan*/  map__fixup_start (struct map*) ; 
 int /*<<< orphan*/  pr_debug (char*,char const*) ; 
 TYPE_1__ symbol_conf ; 
 int /*<<< orphan*/ * vmlinux_path ; 

__attribute__((used)) static int dso__load_kernel_sym(struct dso *dso, struct map *map)
{
	int err;
	const char *kallsyms_filename = NULL;
	char *kallsyms_allocated_filename = NULL;
	/*
	 * Step 1: if the user specified a kallsyms or vmlinux filename, use
	 * it and only it, reporting errors to the user if it cannot be used.
	 *
	 * For instance, try to analyse an ARM perf.data file _without_ a
	 * build-id, or if the user specifies the wrong path to the right
	 * vmlinux file, obviously we can't fallback to another vmlinux (a
	 * x86_86 one, on the machine where analysis is being performed, say),
	 * or worse, /proc/kallsyms.
	 *
	 * If the specified file _has_ a build-id and there is a build-id
	 * section in the perf.data file, we will still do the expected
	 * validation in dso__load_vmlinux and will bail out if they don't
	 * match.
	 */
	if (symbol_conf.kallsyms_name != NULL) {
		kallsyms_filename = symbol_conf.kallsyms_name;
		goto do_kallsyms;
	}

	if (!symbol_conf.ignore_vmlinux && symbol_conf.vmlinux_name != NULL) {
		return dso__load_vmlinux(dso, map, symbol_conf.vmlinux_name, false);
	}

	if (!symbol_conf.ignore_vmlinux && vmlinux_path != NULL) {
		err = dso__load_vmlinux_path(dso, map);
		if (err > 0)
			return err;
	}

	/* do not try local files if a symfs was given */
	if (symbol_conf.symfs[0] != 0)
		return -1;

	kallsyms_allocated_filename = dso__find_kallsyms(dso, map);
	if (!kallsyms_allocated_filename)
		return -1;

	kallsyms_filename = kallsyms_allocated_filename;

do_kallsyms:
	err = dso__load_kallsyms(dso, kallsyms_filename, map);
	if (err > 0)
		pr_debug("Using %s for symbols\n", kallsyms_filename);
	free(kallsyms_allocated_filename);

	if (err > 0 && !dso__is_kcore(dso)) {
		dso->binary_type = DSO_BINARY_TYPE__KALLSYMS;
		dso__set_long_name(dso, DSO__NAME_KALLSYMS, false);
		map__fixup_start(map);
		map__fixup_end(map);
	}

	return err;
}