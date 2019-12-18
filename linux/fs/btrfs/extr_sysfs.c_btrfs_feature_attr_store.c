#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct kobject {int dummy; } ;
struct kobj_attribute {int dummy; } ;
struct btrfs_fs_info {int /*<<< orphan*/  transaction_kthread; int /*<<< orphan*/  super_lock; int /*<<< orphan*/  sb; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
struct TYPE_4__ {TYPE_1__ attr; } ;
struct btrfs_feature_attr {scalar_t__ feature_set; int feature_bit; TYPE_2__ kobj_attr; } ;
typedef  int ssize_t ;

/* Variables and functions */
 int BTRFS_FEATURE_COMPAT_RO_SAFE_CLEAR ; 
 int BTRFS_FEATURE_COMPAT_RO_SAFE_SET ; 
 int BTRFS_FEATURE_COMPAT_SAFE_CLEAR ; 
 int BTRFS_FEATURE_COMPAT_SAFE_SET ; 
 int BTRFS_FEATURE_INCOMPAT_SAFE_CLEAR ; 
 int BTRFS_FEATURE_INCOMPAT_SAFE_SET ; 
 int /*<<< orphan*/  COMMIT ; 
 int EPERM ; 
 int EROFS ; 
 scalar_t__ FEAT_COMPAT ; 
 scalar_t__ FEAT_COMPAT_RO ; 
 int /*<<< orphan*/  btrfs_info (struct btrfs_fs_info*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_pending (struct btrfs_fs_info*,int /*<<< orphan*/ ) ; 
 int get_features (struct btrfs_fs_info*,scalar_t__) ; 
 int kstrtoul (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long*) ; 
 scalar_t__ sb_rdonly (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_features (struct btrfs_fs_info*,scalar_t__,int) ; 
 int /*<<< orphan*/  skip_spaces (char const*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct btrfs_feature_attr* to_btrfs_feature_attr (struct kobj_attribute*) ; 
 struct btrfs_fs_info* to_fs_info (struct kobject*) ; 
 int /*<<< orphan*/  wake_up_process (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t btrfs_feature_attr_store(struct kobject *kobj,
					struct kobj_attribute *a,
					const char *buf, size_t count)
{
	struct btrfs_fs_info *fs_info;
	struct btrfs_feature_attr *fa = to_btrfs_feature_attr(a);
	u64 features, set, clear;
	unsigned long val;
	int ret;

	fs_info = to_fs_info(kobj);
	if (!fs_info)
		return -EPERM;

	if (sb_rdonly(fs_info->sb))
		return -EROFS;

	ret = kstrtoul(skip_spaces(buf), 0, &val);
	if (ret)
		return ret;

	if (fa->feature_set == FEAT_COMPAT) {
		set = BTRFS_FEATURE_COMPAT_SAFE_SET;
		clear = BTRFS_FEATURE_COMPAT_SAFE_CLEAR;
	} else if (fa->feature_set == FEAT_COMPAT_RO) {
		set = BTRFS_FEATURE_COMPAT_RO_SAFE_SET;
		clear = BTRFS_FEATURE_COMPAT_RO_SAFE_CLEAR;
	} else {
		set = BTRFS_FEATURE_INCOMPAT_SAFE_SET;
		clear = BTRFS_FEATURE_INCOMPAT_SAFE_CLEAR;
	}

	features = get_features(fs_info, fa->feature_set);

	/* Nothing to do */
	if ((val && (features & fa->feature_bit)) ||
	    (!val && !(features & fa->feature_bit)))
		return count;

	if ((val && !(set & fa->feature_bit)) ||
	    (!val && !(clear & fa->feature_bit))) {
		btrfs_info(fs_info,
			"%sabling feature %s on mounted fs is not supported.",
			val ? "En" : "Dis", fa->kobj_attr.attr.name);
		return -EPERM;
	}

	btrfs_info(fs_info, "%s %s feature flag",
		   val ? "Setting" : "Clearing", fa->kobj_attr.attr.name);

	spin_lock(&fs_info->super_lock);
	features = get_features(fs_info, fa->feature_set);
	if (val)
		features |= fa->feature_bit;
	else
		features &= ~fa->feature_bit;
	set_features(fs_info, fa->feature_set, features);
	spin_unlock(&fs_info->super_lock);

	/*
	 * We don't want to do full transaction commit from inside sysfs
	 */
	btrfs_set_pending(fs_info, COMMIT);
	wake_up_process(fs_info->transaction_kthread);

	return count;
}