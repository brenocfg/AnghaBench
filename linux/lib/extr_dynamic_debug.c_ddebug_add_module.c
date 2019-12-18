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
struct ddebug_table {char const* mod_name; unsigned int num_ddebugs; int /*<<< orphan*/  link; struct _ddebug* ddebugs; } ;
struct _ddebug {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  ddebug_lock ; 
 int /*<<< orphan*/  ddebug_tables ; 
 struct ddebug_table* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 
 int /*<<< orphan*/  vpr_info (char*,unsigned int,char const*) ; 

int ddebug_add_module(struct _ddebug *tab, unsigned int n,
			     const char *name)
{
	struct ddebug_table *dt;

	dt = kzalloc(sizeof(*dt), GFP_KERNEL);
	if (dt == NULL) {
		pr_err("error adding module: %s\n", name);
		return -ENOMEM;
	}
	/*
	 * For built-in modules, name lives in .rodata and is
	 * immortal. For loaded modules, name points at the name[]
	 * member of struct module, which lives at least as long as
	 * this struct ddebug_table.
	 */
	dt->mod_name = name;
	dt->num_ddebugs = n;
	dt->ddebugs = tab;

	mutex_lock(&ddebug_lock);
	list_add_tail(&dt->link, &ddebug_tables);
	mutex_unlock(&ddebug_lock);

	vpr_info("%u debug prints in module %s\n", n, dt->mod_name);
	return 0;
}