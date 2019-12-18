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
struct TYPE_2__ {int /*<<< orphan*/  drivers_dir; } ;
struct module {int /*<<< orphan*/  holders_dir; TYPE_1__ mkobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_usage_links (struct module*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mod_sysfs_fini (struct module*) ; 
 int /*<<< orphan*/  module_param_sysfs_remove (struct module*) ; 
 int /*<<< orphan*/  module_remove_modinfo_attrs (struct module*,int) ; 

__attribute__((used)) static void mod_sysfs_teardown(struct module *mod)
{
	del_usage_links(mod);
	module_remove_modinfo_attrs(mod, -1);
	module_param_sysfs_remove(mod);
	kobject_put(mod->mkobj.drivers_dir);
	kobject_put(mod->holders_dir);
	mod_sysfs_fini(mod);
}