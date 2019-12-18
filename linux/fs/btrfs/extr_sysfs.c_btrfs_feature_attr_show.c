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
typedef  int u64 ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_feature_attr {int feature_bit; int /*<<< orphan*/  feature_set; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  PAGE_SIZE ; 
 int can_modify_feature (struct btrfs_feature_attr*) ; 
 int get_features (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,int) ; 
 struct btrfs_feature_attr* to_btrfs_feature_attr (struct kobj_attribute*) ; 
 struct btrfs_fs_info* to_fs_info (struct kobject*) ; 

__attribute__((used)) static ssize_t btrfs_feature_attr_show(struct kobject *kobj,
				       struct kobj_attribute *a, char *buf)
{
	int val = 0;
	struct btrfs_fs_info *fs_info = to_fs_info(kobj);
	struct btrfs_feature_attr *fa = to_btrfs_feature_attr(a);
	if (fs_info) {
		u64 features = get_features(fs_info, fa->feature_set);
		if (features & fa->feature_bit)
			val = 1;
	} else
		val = can_modify_feature(fa);

	return snprintf(buf, PAGE_SIZE, "%d\n", val);
}