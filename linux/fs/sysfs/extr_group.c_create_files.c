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
typedef  int umode_t ;
struct kobject {int dummy; } ;
struct kernfs_node {int dummy; } ;
struct attribute {int mode; int /*<<< orphan*/  name; } ;
struct bin_attribute {struct attribute attr; } ;
struct attribute_group {int (* is_visible ) (struct kobject*,struct attribute* const,int) ;int (* is_bin_visible ) (struct kobject*,struct bin_attribute* const,int) ;struct bin_attribute** bin_attrs; struct attribute** attrs; } ;
typedef  int /*<<< orphan*/  kuid_t ;
typedef  int /*<<< orphan*/  kgid_t ;

/* Variables and functions */
 int SYSFS_PREALLOC ; 
 int /*<<< orphan*/  WARN (int,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  kernfs_remove_by_name (struct kernfs_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_files (struct kernfs_node*,struct attribute_group const*) ; 
 int stub1 (struct kobject*,struct attribute* const,int) ; 
 int stub2 (struct kobject*,struct bin_attribute* const,int) ; 
 int sysfs_add_file_mode_ns (struct kernfs_node*,struct attribute* const,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int create_files(struct kernfs_node *parent, struct kobject *kobj,
			kuid_t uid, kgid_t gid,
			const struct attribute_group *grp, int update)
{
	struct attribute *const *attr;
	struct bin_attribute *const *bin_attr;
	int error = 0, i;

	if (grp->attrs) {
		for (i = 0, attr = grp->attrs; *attr && !error; i++, attr++) {
			umode_t mode = (*attr)->mode;

			/*
			 * In update mode, we're changing the permissions or
			 * visibility.  Do this by first removing then
			 * re-adding (if required) the file.
			 */
			if (update)
				kernfs_remove_by_name(parent, (*attr)->name);
			if (grp->is_visible) {
				mode = grp->is_visible(kobj, *attr, i);
				if (!mode)
					continue;
			}

			WARN(mode & ~(SYSFS_PREALLOC | 0664),
			     "Attribute %s: Invalid permissions 0%o\n",
			     (*attr)->name, mode);

			mode &= SYSFS_PREALLOC | 0664;
			error = sysfs_add_file_mode_ns(parent, *attr, false,
						       mode, uid, gid, NULL);
			if (unlikely(error))
				break;
		}
		if (error) {
			remove_files(parent, grp);
			goto exit;
		}
	}

	if (grp->bin_attrs) {
		for (i = 0, bin_attr = grp->bin_attrs; *bin_attr; i++, bin_attr++) {
			umode_t mode = (*bin_attr)->attr.mode;

			if (update)
				kernfs_remove_by_name(parent,
						(*bin_attr)->attr.name);
			if (grp->is_bin_visible) {
				mode = grp->is_bin_visible(kobj, *bin_attr, i);
				if (!mode)
					continue;
			}

			WARN(mode & ~(SYSFS_PREALLOC | 0664),
			     "Attribute %s: Invalid permissions 0%o\n",
			     (*bin_attr)->attr.name, mode);

			mode &= SYSFS_PREALLOC | 0664;
			error = sysfs_add_file_mode_ns(parent,
					&(*bin_attr)->attr, true,
					mode,
					uid, gid, NULL);
			if (error)
				break;
		}
		if (error)
			remove_files(parent, grp);
	}
exit:
	return error;
}