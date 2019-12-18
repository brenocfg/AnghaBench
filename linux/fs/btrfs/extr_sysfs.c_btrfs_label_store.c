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
struct btrfs_fs_info {int /*<<< orphan*/  transaction_kthread; int /*<<< orphan*/  super_lock; TYPE_1__* super_copy; int /*<<< orphan*/  sb; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  label; } ;

/* Variables and functions */
 size_t BTRFS_LABEL_SIZE ; 
 int /*<<< orphan*/  COMMIT ; 
 size_t EINVAL ; 
 size_t EPERM ; 
 size_t EROFS ; 
 int /*<<< orphan*/  btrfs_set_pending (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ sb_rdonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 size_t strcspn (char const*,char*) ; 
 struct btrfs_fs_info* to_fs_info (struct kobject*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t btrfs_label_store(struct kobject *kobj,
				 struct kobj_attribute *a,
				 const char *buf, size_t len)
{
	struct btrfs_fs_info *fs_info = to_fs_info(kobj);
	size_t p_len;

	if (!fs_info)
		return -EPERM;

	if (sb_rdonly(fs_info->sb))
		return -EROFS;

	/*
	 * p_len is the len until the first occurrence of either
	 * '\n' or '\0'
	 */
	p_len = strcspn(buf, "\n");

	if (p_len >= BTRFS_LABEL_SIZE)
		return -EINVAL;

	spin_lock(&fs_info->super_lock);
	memset(fs_info->super_copy->label, 0, BTRFS_LABEL_SIZE);
	memcpy(fs_info->super_copy->label, buf, p_len);
	spin_unlock(&fs_info->super_lock);

	/*
	 * We don't want to do full transaction commit from inside sysfs
	 */
	btrfs_set_pending(fs_info, COMMIT);
	wake_up_process(fs_info->transaction_kthread);

	return len;
}