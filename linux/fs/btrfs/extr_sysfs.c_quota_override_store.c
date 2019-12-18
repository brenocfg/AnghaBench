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
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  flags; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_OVERRIDE ; 
 int /*<<< orphan*/  CAP_SYS_RESOURCE ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int kstrtoul (char const*,int,unsigned long*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* to_fs_info (struct kobject*) ; 

__attribute__((used)) static ssize_t quota_override_store(struct kobject *kobj,
				    struct kobj_attribute *a,
				    const char *buf, size_t len)
{
	struct btrfs_fs_info *fs_info = to_fs_info(kobj);
	unsigned long knob;
	int err;

	if (!fs_info)
		return -EPERM;

	if (!capable(CAP_SYS_RESOURCE))
		return -EPERM;

	err = kstrtoul(buf, 10, &knob);
	if (err)
		return err;
	if (knob > 1)
		return -EINVAL;

	if (knob)
		set_bit(BTRFS_FS_QUOTA_OVERRIDE, &fs_info->flags);
	else
		clear_bit(BTRFS_FS_QUOTA_OVERRIDE, &fs_info->flags);

	return len;
}