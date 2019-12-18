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
struct kobj_type {int /*<<< orphan*/  default_groups; } ;
struct kobj_ns_type_operations {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ KOBJ_NS_TYPES ; 
 scalar_t__ KOBJ_NS_TYPE_NONE ; 
 struct kobj_type* get_ktype (struct kobject*) ; 
 struct kobj_ns_type_operations* kobj_child_ns_ops (struct kobject*) ; 
 int /*<<< orphan*/  kobj_ns_type_registered (scalar_t__) ; 
 int /*<<< orphan*/  kobject_namespace (struct kobject*) ; 
 int populate_dir (struct kobject*) ; 
 int sysfs_create_dir_ns (struct kobject*,int /*<<< orphan*/ ) ; 
 int sysfs_create_groups (struct kobject*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_enable_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_remove_dir (struct kobject*) ; 

__attribute__((used)) static int create_dir(struct kobject *kobj)
{
	const struct kobj_type *ktype = get_ktype(kobj);
	const struct kobj_ns_type_operations *ops;
	int error;

	error = sysfs_create_dir_ns(kobj, kobject_namespace(kobj));
	if (error)
		return error;

	error = populate_dir(kobj);
	if (error) {
		sysfs_remove_dir(kobj);
		return error;
	}

	if (ktype) {
		error = sysfs_create_groups(kobj, ktype->default_groups);
		if (error) {
			sysfs_remove_dir(kobj);
			return error;
		}
	}

	/*
	 * @kobj->sd may be deleted by an ancestor going away.  Hold an
	 * extra reference so that it stays until @kobj is gone.
	 */
	sysfs_get(kobj->sd);

	/*
	 * If @kobj has ns_ops, its children need to be filtered based on
	 * their namespace tags.  Enable namespace support on @kobj->sd.
	 */
	ops = kobj_child_ns_ops(kobj);
	if (ops) {
		BUG_ON(ops->type <= KOBJ_NS_TYPE_NONE);
		BUG_ON(ops->type >= KOBJ_NS_TYPES);
		BUG_ON(!kobj_ns_type_registered(ops->type));

		sysfs_enable_ns(kobj->sd);
	}

	return 0;
}