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
struct module {scalar_t__ state; int /*<<< orphan*/  list; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int EEXIST ; 
 scalar_t__ MODULE_STATE_LIVE ; 
 scalar_t__ MODULE_STATE_UNFORMED ; 
 struct module* find_module_all (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  finished_loading (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_tree_insert (struct module*) ; 
 int /*<<< orphan*/  mod_update_bounds (struct module*) ; 
 int /*<<< orphan*/  module_mutex ; 
 int /*<<< orphan*/  module_wq ; 
 int /*<<< orphan*/  modules ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int wait_event_interruptible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_unformed_module(struct module *mod)
{
	int err;
	struct module *old;

	mod->state = MODULE_STATE_UNFORMED;

again:
	mutex_lock(&module_mutex);
	old = find_module_all(mod->name, strlen(mod->name), true);
	if (old != NULL) {
		if (old->state != MODULE_STATE_LIVE) {
			/* Wait in case it fails to load. */
			mutex_unlock(&module_mutex);
			err = wait_event_interruptible(module_wq,
					       finished_loading(mod->name));
			if (err)
				goto out_unlocked;
			goto again;
		}
		err = -EEXIST;
		goto out;
	}
	mod_update_bounds(mod);
	list_add_rcu(&mod->list, &modules);
	mod_tree_insert(mod);
	err = 0;

out:
	mutex_unlock(&module_mutex);
out_unlocked:
	return err;
}