#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_3__ {scalar_t__ s_journal; } ;

/* Variables and functions */
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext4_commit_super (struct super_block*,int) ; 
 scalar_t__ ext4_forced_shutdown (TYPE_1__*) ; 
 int /*<<< orphan*/  ext4_set_feature_journal_needs_recovery (struct super_block*) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 

__attribute__((used)) static int ext4_unfreeze(struct super_block *sb)
{
	if (sb_rdonly(sb) || ext4_forced_shutdown(EXT4_SB(sb)))
		return 0;

	if (EXT4_SB(sb)->s_journal) {
		/* Reset the needs_recovery flag before the fs is unlocked. */
		ext4_set_feature_journal_needs_recovery(sb);
	}

	ext4_commit_super(sb, 1);
	return 0;
}