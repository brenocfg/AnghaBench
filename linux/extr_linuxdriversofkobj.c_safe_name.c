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
struct kobject {int /*<<< orphan*/  sd; } ;
struct kernfs_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 char* kasprintf (int /*<<< orphan*/ ,char*,char const*,int) ; 
 int /*<<< orphan*/  kfree (char const*) ; 
 int /*<<< orphan*/  kobject_name (struct kobject*) ; 
 char* kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,char const*) ; 
 struct kernfs_node* sysfs_get_dirent (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sysfs_put (struct kernfs_node*) ; 

__attribute__((used)) static const char *safe_name(struct kobject *kobj, const char *orig_name)
{
	const char *name = orig_name;
	struct kernfs_node *kn;
	int i = 0;

	/* don't be a hero. After 16 tries give up */
	while (i < 16 && (kn = sysfs_get_dirent(kobj->sd, name))) {
		sysfs_put(kn);
		if (name != orig_name)
			kfree(name);
		name = kasprintf(GFP_KERNEL, "%s#%i", orig_name, ++i);
	}

	if (name == orig_name) {
		name = kstrdup(orig_name, GFP_KERNEL);
	} else {
		pr_warn("Duplicate name in %s, renamed to \"%s\"\n",
			kobject_name(kobj), name);
	}
	return name;
}