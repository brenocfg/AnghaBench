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
typedef  int /*<<< orphan*/  umode_t ;
typedef  int u64 ;
struct kobject {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_feature_attr {int feature_bit; int /*<<< orphan*/  feature_set; } ;
struct attribute {int /*<<< orphan*/  mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  S_IWUSR ; 
 struct btrfs_feature_attr* attr_to_btrfs_feature_attr (struct attribute*) ; 
 scalar_t__ can_modify_feature (struct btrfs_feature_attr*) ; 
 int get_features (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 struct btrfs_fs_info* to_fs_info (struct kobject*) ; 

__attribute__((used)) static umode_t btrfs_feature_visible(struct kobject *kobj,
				     struct attribute *attr, int unused)
{
	struct btrfs_fs_info *fs_info = to_fs_info(kobj);
	umode_t mode = attr->mode;

	if (fs_info) {
		struct btrfs_feature_attr *fa;
		u64 features;

		fa = attr_to_btrfs_feature_attr(attr);
		features = get_features(fs_info, fa->feature_set);

		if (can_modify_feature(fa))
			mode |= S_IWUSR;
		else if (!(features & fa->feature_bit))
			mode = 0;
	}

	return mode;
}