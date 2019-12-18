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
struct module {int /*<<< orphan*/  state; } ;
struct load_info {int /*<<< orphan*/  sechdrs; int /*<<< orphan*/  hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  MODULE_STATE_COMING ; 
 int /*<<< orphan*/  module_bug_finalize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct module*) ; 
 int /*<<< orphan*/  module_enable_nx (struct module*) ; 
 int /*<<< orphan*/  module_enable_ro (struct module*,int) ; 
 int /*<<< orphan*/  module_enable_x (struct module*) ; 
 int /*<<< orphan*/  module_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int verify_exported_symbols (struct module*) ; 

__attribute__((used)) static int complete_formation(struct module *mod, struct load_info *info)
{
	int err;

	mutex_lock(&module_mutex);

	/* Find duplicate symbols (must be called under lock). */
	err = verify_exported_symbols(mod);
	if (err < 0)
		goto out;

	/* This relies on module_mutex for list integrity. */
	module_bug_finalize(info->hdr, info->sechdrs, mod);

	module_enable_ro(mod, false);
	module_enable_nx(mod);
	module_enable_x(mod);

	/* Mark state as coming so strong_try_module_get() ignores us,
	 * but kallsyms etc. can see us. */
	mod->state = MODULE_STATE_COMING;
	mutex_unlock(&module_mutex);

	return 0;

out:
	mutex_unlock(&module_mutex);
	return err;
}