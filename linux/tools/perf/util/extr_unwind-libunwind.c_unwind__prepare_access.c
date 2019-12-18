#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct unwind_libunwind_ops {int dummy; } ;
struct map_groups {TYPE_1__* unwind_libunwind_ops; TYPE_4__* machine; scalar_t__ addr_space; } ;
struct map {TYPE_3__* dso; } ;
typedef  enum dso_type { ____Placeholder_dso_type } dso_type ;
struct TYPE_8__ {TYPE_2__* env; } ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_6__ {int /*<<< orphan*/  arch; } ;
struct TYPE_5__ {int (* prepare_access ) (struct map_groups*) ;} ;

/* Variables and functions */
 int DSO__TYPE_64BIT ; 
 int DSO__TYPE_UNKNOWN ; 
 struct unwind_libunwind_ops* arm64_unwind_libunwind_ops ; 
 int dso__type (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  dwarf_callchain_users ; 
 struct unwind_libunwind_ops* local_unwind_libunwind_ops ; 
 char* perf_env__arch (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int stub1 (struct map_groups*) ; 
 int /*<<< orphan*/  unwind__register_ops (struct map_groups*,struct unwind_libunwind_ops*) ; 
 struct unwind_libunwind_ops* x86_32_unwind_libunwind_ops ; 

int unwind__prepare_access(struct map_groups *mg, struct map *map,
			   bool *initialized)
{
	const char *arch;
	enum dso_type dso_type;
	struct unwind_libunwind_ops *ops = local_unwind_libunwind_ops;
	int err;

	if (!dwarf_callchain_users)
		return 0;

	if (mg->addr_space) {
		pr_debug("unwind: thread map already set, dso=%s\n",
			 map->dso->name);
		if (initialized)
			*initialized = true;
		return 0;
	}

	/* env->arch is NULL for live-mode (i.e. perf top) */
	if (!mg->machine->env || !mg->machine->env->arch)
		goto out_register;

	dso_type = dso__type(map->dso, mg->machine);
	if (dso_type == DSO__TYPE_UNKNOWN)
		return 0;

	arch = perf_env__arch(mg->machine->env);

	if (!strcmp(arch, "x86")) {
		if (dso_type != DSO__TYPE_64BIT)
			ops = x86_32_unwind_libunwind_ops;
	} else if (!strcmp(arch, "arm64") || !strcmp(arch, "arm")) {
		if (dso_type == DSO__TYPE_64BIT)
			ops = arm64_unwind_libunwind_ops;
	}

	if (!ops) {
		pr_err("unwind: target platform=%s is not supported\n", arch);
		return 0;
	}
out_register:
	unwind__register_ops(mg, ops);

	err = mg->unwind_libunwind_ops->prepare_access(mg);
	if (initialized)
		*initialized = err ? false : true;
	return err;
}