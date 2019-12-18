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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  super_lock; TYPE_1__* super_copy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {char* label; } ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* to_fs_info (struct kobject*) ; 

__attribute__((used)) static ssize_t btrfs_label_show(struct kobject *kobj,
				struct kobj_attribute *a, char *buf)
{
	struct btrfs_fs_info *fs_info = to_fs_info(kobj);
	char *label = fs_info->super_copy->label;
	ssize_t ret;

	spin_lock(&fs_info->super_lock);
	ret = snprintf(buf, PAGE_SIZE, label[0] ? "%s\n" : "%s", label);
	spin_unlock(&fs_info->super_lock);

	return ret;
}