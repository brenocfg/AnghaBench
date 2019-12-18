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
struct kset {int dummy; } ;
struct kobject {struct kset* kset; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ kobject_init_and_add (struct kobject*,int /*<<< orphan*/ *,struct kobject*,char*,char const*) ; 
 int /*<<< orphan*/  kobject_put (struct kobject*) ; 
 struct kobject* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_netns_object_type ; 

__attribute__((used)) static struct kobject *nfs_netns_object_alloc(const char *name,
		struct kset *kset, struct kobject *parent)
{
	struct kobject *kobj;

	kobj = kzalloc(sizeof(*kobj), GFP_KERNEL);
	if (kobj) {
		kobj->kset = kset;
		if (kobject_init_and_add(kobj, &nfs_netns_object_type,
					parent, "%s", name) == 0)
			return kobj;
		kobject_put(kobj);
	}
	return NULL;
}