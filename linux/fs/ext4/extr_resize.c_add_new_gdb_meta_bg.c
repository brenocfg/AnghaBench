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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;
typedef  unsigned long ext4_group_t ;
typedef  scalar_t__ ext4_fsblk_t ;
struct TYPE_2__ {int s_gdb_count; struct buffer_head** s_group_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUFFER_TRACE (struct buffer_head*,char*) ; 
 int ENOMEM ; 
 unsigned long EXT4_DESC_PER_BLOCK (struct super_block*) ; 
 TYPE_1__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct buffer_head*) ; 
 int PTR_ERR (struct buffer_head*) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ ext4_bg_has_super (struct super_block*,unsigned long) ; 
 int ext4_journal_get_write_access (int /*<<< orphan*/ *,struct buffer_head*) ; 
 struct buffer_head** ext4_kvmalloc (unsigned long,int /*<<< orphan*/ ) ; 
 scalar_t__ ext4_meta_bg_first_block_no (struct super_block*,unsigned long) ; 
 struct buffer_head* ext4_sb_bread (struct super_block*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_warning (struct super_block*,char*,unsigned long) ; 
 int /*<<< orphan*/  kvfree (struct buffer_head**) ; 
 int /*<<< orphan*/  memcpy (struct buffer_head**,struct buffer_head**,int) ; 

__attribute__((used)) static int add_new_gdb_meta_bg(struct super_block *sb,
			       handle_t *handle, ext4_group_t group) {
	ext4_fsblk_t gdblock;
	struct buffer_head *gdb_bh;
	struct buffer_head **o_group_desc, **n_group_desc;
	unsigned long gdb_num = group / EXT4_DESC_PER_BLOCK(sb);
	int err;

	gdblock = ext4_meta_bg_first_block_no(sb, group) +
		   ext4_bg_has_super(sb, group);
	gdb_bh = ext4_sb_bread(sb, gdblock, 0);
	if (IS_ERR(gdb_bh))
		return PTR_ERR(gdb_bh);
	n_group_desc = ext4_kvmalloc((gdb_num + 1) *
				     sizeof(struct buffer_head *),
				     GFP_NOFS);
	if (!n_group_desc) {
		brelse(gdb_bh);
		err = -ENOMEM;
		ext4_warning(sb, "not enough memory for %lu groups",
			     gdb_num + 1);
		return err;
	}

	o_group_desc = EXT4_SB(sb)->s_group_desc;
	memcpy(n_group_desc, o_group_desc,
	       EXT4_SB(sb)->s_gdb_count * sizeof(struct buffer_head *));
	n_group_desc[gdb_num] = gdb_bh;

	BUFFER_TRACE(gdb_bh, "get_write_access");
	err = ext4_journal_get_write_access(handle, gdb_bh);
	if (err) {
		kvfree(n_group_desc);
		brelse(gdb_bh);
		return err;
	}

	EXT4_SB(sb)->s_group_desc = n_group_desc;
	EXT4_SB(sb)->s_gdb_count++;
	kvfree(o_group_desc);
	return err;
}