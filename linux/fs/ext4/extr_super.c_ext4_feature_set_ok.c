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
struct super_block {int /*<<< orphan*/  s_flags; } ;
struct TYPE_4__ {TYPE_1__* s_es; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_feature_ro_compat; int /*<<< orphan*/  s_feature_incompat; } ;

/* Variables and functions */
 int EXT4_FEATURE_INCOMPAT_SUPP ; 
 int EXT4_FEATURE_RO_COMPAT_SUPP ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  SB_RDONLY ; 
 scalar_t__ ext4_has_feature_bigalloc (struct super_block*) ; 
 scalar_t__ ext4_has_feature_casefold (struct super_block*) ; 
 int /*<<< orphan*/  ext4_has_feature_extents (struct super_block*) ; 
 scalar_t__ ext4_has_feature_project (struct super_block*) ; 
 scalar_t__ ext4_has_feature_quota (struct super_block*) ; 
 scalar_t__ ext4_has_feature_readonly (struct super_block*) ; 
 scalar_t__ ext4_has_unknown_ext4_incompat_features (struct super_block*) ; 
 scalar_t__ ext4_has_unknown_ext4_ro_compat_features (struct super_block*) ; 
 int /*<<< orphan*/  ext4_msg (struct super_block*,int /*<<< orphan*/ ,char*,...) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ext4_feature_set_ok(struct super_block *sb, int readonly)
{
	if (ext4_has_unknown_ext4_incompat_features(sb)) {
		ext4_msg(sb, KERN_ERR,
			"Couldn't mount because of "
			"unsupported optional features (%x)",
			(le32_to_cpu(EXT4_SB(sb)->s_es->s_feature_incompat) &
			~EXT4_FEATURE_INCOMPAT_SUPP));
		return 0;
	}

#ifndef CONFIG_UNICODE
	if (ext4_has_feature_casefold(sb)) {
		ext4_msg(sb, KERN_ERR,
			 "Filesystem with casefold feature cannot be "
			 "mounted without CONFIG_UNICODE");
		return 0;
	}
#endif

	if (readonly)
		return 1;

	if (ext4_has_feature_readonly(sb)) {
		ext4_msg(sb, KERN_INFO, "filesystem is read-only");
		sb->s_flags |= SB_RDONLY;
		return 1;
	}

	/* Check that feature set is OK for a read-write mount */
	if (ext4_has_unknown_ext4_ro_compat_features(sb)) {
		ext4_msg(sb, KERN_ERR, "couldn't mount RDWR because of "
			 "unsupported optional features (%x)",
			 (le32_to_cpu(EXT4_SB(sb)->s_es->s_feature_ro_compat) &
				~EXT4_FEATURE_RO_COMPAT_SUPP));
		return 0;
	}
	if (ext4_has_feature_bigalloc(sb) && !ext4_has_feature_extents(sb)) {
		ext4_msg(sb, KERN_ERR,
			 "Can't support bigalloc feature without "
			 "extents feature\n");
		return 0;
	}

#ifndef CONFIG_QUOTA
	if (ext4_has_feature_quota(sb) && !readonly) {
		ext4_msg(sb, KERN_ERR,
			 "Filesystem with quota feature cannot be mounted RDWR "
			 "without CONFIG_QUOTA");
		return 0;
	}
	if (ext4_has_feature_project(sb) && !readonly) {
		ext4_msg(sb, KERN_ERR,
			 "Filesystem with project quota feature cannot be mounted RDWR "
			 "without CONFIG_QUOTA");
		return 0;
	}
#endif  /* CONFIG_QUOTA */
	return 1;
}