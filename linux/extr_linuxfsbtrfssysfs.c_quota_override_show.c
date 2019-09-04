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
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FS_QUOTA_OVERRIDE ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 int test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct btrfs_fs_info* to_fs_info (struct kobject*) ; 

__attribute__((used)) static ssize_t quota_override_show(struct kobject *kobj,
				   struct kobj_attribute *a, char *buf)
{
	struct btrfs_fs_info *fs_info = to_fs_info(kobj);
	int quota_override;

	quota_override = test_bit(BTRFS_FS_QUOTA_OVERRIDE, &fs_info->flags);
	return snprintf(buf, PAGE_SIZE, "%d\n", quota_override);
}