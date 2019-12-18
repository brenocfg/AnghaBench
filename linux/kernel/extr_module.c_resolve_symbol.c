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
struct module {int taints; } ;
struct load_info {int dummy; } ;
struct kernel_symbol {int dummy; } ;
typedef  int /*<<< orphan*/  s32 ;

/* Variables and functions */
 int EINVAL ; 
 struct kernel_symbol* ERR_PTR (int) ; 
 int /*<<< orphan*/  MODULE_NAME_LEN ; 
 int TAINT_PROPRIETARY_MODULE ; 
 int /*<<< orphan*/  check_version (struct load_info const*,char const*,struct module*,int /*<<< orphan*/  const*) ; 
 struct kernel_symbol* find_symbol (char const*,struct module**,int /*<<< orphan*/  const**,int,int) ; 
 int /*<<< orphan*/  module_mutex ; 
 int /*<<< orphan*/  module_name (struct module*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ref_module (struct module*,struct module*) ; 
 int /*<<< orphan*/  sched_annotate_sleep () ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int verify_namespace_is_imported (struct load_info const*,struct kernel_symbol const*,struct module*) ; 

__attribute__((used)) static const struct kernel_symbol *resolve_symbol(struct module *mod,
						  const struct load_info *info,
						  const char *name,
						  char ownername[])
{
	struct module *owner;
	const struct kernel_symbol *sym;
	const s32 *crc;
	int err;

	/*
	 * The module_mutex should not be a heavily contended lock;
	 * if we get the occasional sleep here, we'll go an extra iteration
	 * in the wait_event_interruptible(), which is harmless.
	 */
	sched_annotate_sleep();
	mutex_lock(&module_mutex);
	sym = find_symbol(name, &owner, &crc,
			  !(mod->taints & (1 << TAINT_PROPRIETARY_MODULE)), true);
	if (!sym)
		goto unlock;

	if (!check_version(info, name, mod, crc)) {
		sym = ERR_PTR(-EINVAL);
		goto getname;
	}

	err = verify_namespace_is_imported(info, sym, mod);
	if (err) {
		sym = ERR_PTR(err);
		goto getname;
	}

	err = ref_module(mod, owner);
	if (err) {
		sym = ERR_PTR(err);
		goto getname;
	}

getname:
	/* We must make copy under the lock if we failed to get ref. */
	strncpy(ownername, module_name(owner), MODULE_NAME_LEN);
unlock:
	mutex_unlock(&module_mutex);
	return sym;
}