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
struct super_block {int dummy; } ;
struct msdos_sb_info {scalar_t__ dirty; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct TYPE_3__ {int /*<<< orphan*/  state; } ;
struct fat_boot_sector {TYPE_2__ fat16; TYPE_1__ fat32; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FAT_STATE_DIRTY ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 struct msdos_sb_info* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  fat_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_fat32 (struct msdos_sb_info*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 struct buffer_head* sb_bread (struct super_block*,int /*<<< orphan*/ ) ; 
 scalar_t__ sb_rdonly (struct super_block*) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 

__attribute__((used)) static void fat_set_state(struct super_block *sb,
			unsigned int set, unsigned int force)
{
	struct buffer_head *bh;
	struct fat_boot_sector *b;
	struct msdos_sb_info *sbi = MSDOS_SB(sb);

	/* do not change any thing if mounted read only */
	if (sb_rdonly(sb) && !force)
		return;

	/* do not change state if fs was dirty */
	if (sbi->dirty) {
		/* warn only on set (mount). */
		if (set)
			fat_msg(sb, KERN_WARNING, "Volume was not properly "
				"unmounted. Some data may be corrupt. "
				"Please run fsck.");
		return;
	}

	bh = sb_bread(sb, 0);
	if (bh == NULL) {
		fat_msg(sb, KERN_ERR, "unable to read boot sector "
			"to mark fs as dirty");
		return;
	}

	b = (struct fat_boot_sector *) bh->b_data;

	if (is_fat32(sbi)) {
		if (set)
			b->fat32.state |= FAT_STATE_DIRTY;
		else
			b->fat32.state &= ~FAT_STATE_DIRTY;
	} else /* fat 16 and 12 */ {
		if (set)
			b->fat16.state |= FAT_STATE_DIRTY;
		else
			b->fat16.state &= ~FAT_STATE_DIRTY;
	}

	mark_buffer_dirty(bh);
	sync_dirty_buffer(bh);
	brelse(bh);
}