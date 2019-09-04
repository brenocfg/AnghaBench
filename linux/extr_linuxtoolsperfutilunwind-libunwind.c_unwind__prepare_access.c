#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct unwind_libunwind_ops {int dummy; } ;
struct thread {TYPE_2__* unwind_libunwind_ops; TYPE_1__* mg; scalar_t__ addr_space; } ;
struct map {TYPE_4__* dso; } ;
typedef  enum dso_type { ____Placeholder_dso_type } dso_type ;
struct TYPE_10__ {TYPE_3__* env; } ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {int /*<<< orphan*/  arch; } ;
struct TYPE_7__ {int (* prepare_access ) (struct thread*) ;} ;
struct TYPE_6__ {TYPE_5__* machine; } ;

/* Variables and functions */
 int DSO__TYPE_64BIT ; 
 int DSO__TYPE_UNKNOWN ; 
 struct unwind_libunwind_ops* arm64_unwind_libunwind_ops ; 
 int dso__type (TYPE_4__*,TYPE_5__*) ; 
 struct unwind_libunwind_ops* local_unwind_libunwind_ops ; 
 char* perf_env__arch (TYPE_3__*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int stub1 (struct thread*) ; 
 int /*<<< orphan*/  unwind__register_ops (struct thread*,struct unwind_libunwind_ops*) ; 
 struct unwind_libunwind_ops* x86_32_unwind_libunwind_ops ; 

int unwind__prepare_access(struct thread *thread, struct map *map,
			   bool *initialized)
{
	const char *arch;
	enum dso_type dso_type;
	struct unwind_libunwind_ops *ops = local_unwind_libunwind_ops;
	int err;

	if (thread->addr_space) {
		pr_debug("unwind: thread map already set, dso=%s\n",
			 map->dso->name);
		if (initialized)
			*initialized = true;
		return 0;
	}

	/* env->arch is NULL for live-mode (i.e. perf top) */
	if (!thread->mg->machine->env || !thread->mg->machine->env->arch)
		goto out_register;

	dso_type = dso__type(map->dso, thread->mg->machine);
	if (dso_type == DSO__TYPE_UNKNOWN)
		return 0;

	arch = perf_env__arch(thread->mg->machine->env);

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
	unwind__register_ops(thread, ops);

	err = thread->unwind_libunwind_ops->prepare_access(thread);
	if (initialized)
		*initialized = err ? false : true;
	return err;
}