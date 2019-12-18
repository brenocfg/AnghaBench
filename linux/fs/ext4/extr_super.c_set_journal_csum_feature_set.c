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
struct ext4_sb_info {int /*<<< orphan*/  s_journal; } ;

/* Variables and functions */
 struct ext4_sb_info* EXT4_SB (struct super_block*) ; 
 int JBD2_FEATURE_COMPAT_CHECKSUM ; 
 int JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT ; 
 int JBD2_FEATURE_INCOMPAT_CSUM_V2 ; 
 int JBD2_FEATURE_INCOMPAT_CSUM_V3 ; 
 int /*<<< orphan*/  JOURNAL_ASYNC_COMMIT ; 
 int /*<<< orphan*/  JOURNAL_CHECKSUM ; 
 scalar_t__ ext4_has_metadata_csum (struct super_block*) ; 
 int /*<<< orphan*/  jbd2_journal_clear_features (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int jbd2_journal_set_features (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int set_journal_csum_feature_set(struct super_block *sb)
{
	int ret = 1;
	int compat, incompat;
	struct ext4_sb_info *sbi = EXT4_SB(sb);

	if (ext4_has_metadata_csum(sb)) {
		/* journal checksum v3 */
		compat = 0;
		incompat = JBD2_FEATURE_INCOMPAT_CSUM_V3;
	} else {
		/* journal checksum v1 */
		compat = JBD2_FEATURE_COMPAT_CHECKSUM;
		incompat = 0;
	}

	jbd2_journal_clear_features(sbi->s_journal,
			JBD2_FEATURE_COMPAT_CHECKSUM, 0,
			JBD2_FEATURE_INCOMPAT_CSUM_V3 |
			JBD2_FEATURE_INCOMPAT_CSUM_V2);
	if (test_opt(sb, JOURNAL_ASYNC_COMMIT)) {
		ret = jbd2_journal_set_features(sbi->s_journal,
				compat, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT |
				incompat);
	} else if (test_opt(sb, JOURNAL_CHECKSUM)) {
		ret = jbd2_journal_set_features(sbi->s_journal,
				compat, 0,
				incompat);
		jbd2_journal_clear_features(sbi->s_journal, 0, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);
	} else {
		jbd2_journal_clear_features(sbi->s_journal, 0, 0,
				JBD2_FEATURE_INCOMPAT_ASYNC_COMMIT);
	}

	return ret;
}