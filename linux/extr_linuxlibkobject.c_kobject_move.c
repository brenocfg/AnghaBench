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
struct kobject {struct kobject* parent; TYPE_1__* kset; } ;
struct TYPE_2__ {struct kobject kobj; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KOBJ_MOVE ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 char* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct kobject* kobject_get (struct kobject*) ; 
 char* kobject_get_path (struct kobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_namespace (struct kobject*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 int /*<<< orphan*/  kobject_uevent_env (struct kobject*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sprintf (char*,char*,char const*) ; 
 scalar_t__ strlen (char const*) ; 
 int sysfs_move_dir_ns (struct kobject*,struct kobject*,int /*<<< orphan*/ ) ; 

int kobject_move(struct kobject *kobj, struct kobject *new_parent)
{
	int error;
	struct kobject *old_parent;
	const char *devpath = NULL;
	char *devpath_string = NULL;
	char *envp[2];

	kobj = kobject_get(kobj);
	if (!kobj)
		return -EINVAL;
	new_parent = kobject_get(new_parent);
	if (!new_parent) {
		if (kobj->kset)
			new_parent = kobject_get(&kobj->kset->kobj);
	}

	/* old object path */
	devpath = kobject_get_path(kobj, GFP_KERNEL);
	if (!devpath) {
		error = -ENOMEM;
		goto out;
	}
	devpath_string = kmalloc(strlen(devpath) + 15, GFP_KERNEL);
	if (!devpath_string) {
		error = -ENOMEM;
		goto out;
	}
	sprintf(devpath_string, "DEVPATH_OLD=%s", devpath);
	envp[0] = devpath_string;
	envp[1] = NULL;
	error = sysfs_move_dir_ns(kobj, new_parent, kobject_namespace(kobj));
	if (error)
		goto out;
	old_parent = kobj->parent;
	kobj->parent = new_parent;
	new_parent = NULL;
	kobject_put(old_parent);
	kobject_uevent_env(kobj, KOBJ_MOVE, envp);
out:
	kobject_put(new_parent);
	kobject_put(kobj);
	kfree(devpath_string);
	kfree(devpath);
	return error;
}