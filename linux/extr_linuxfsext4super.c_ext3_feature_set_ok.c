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
struct super_block {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ext4_has_feature_journal (struct super_block*) ; 
 scalar_t__ ext4_has_unknown_ext3_incompat_features (struct super_block*) ; 
 scalar_t__ ext4_has_unknown_ext3_ro_compat_features (struct super_block*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 

__attribute__((used)) static inline int ext3_feature_set_ok(struct super_block *sb)
{
	if (ext4_has_unknown_ext3_incompat_features(sb))
		return 0;
	if (!ext4_has_feature_journal(sb))
		return 0;
	if (sb_rdonly(sb))
		return 1;
	if (ext4_has_unknown_ext3_ro_compat_features(sb))
		return 0;
	return 1;
}