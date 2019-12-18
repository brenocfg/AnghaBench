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
struct super_block {int s_flags; } ;
struct qstr {int dummy; } ;
struct inode {int /*<<< orphan*/  i_flags; scalar_t__ i_ino; scalar_t__ i_generation; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; scalar_t__ i_blocks; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct ext2_super_block {int /*<<< orphan*/  s_inodes_count; } ;
struct ext2_sb_info {int s_groups_count; int* s_debts; int /*<<< orphan*/  s_next_gen_lock; int /*<<< orphan*/  s_next_generation; int /*<<< orphan*/  s_dirs_counter; int /*<<< orphan*/  s_freeinodes_counter; struct ext2_super_block* s_es; } ;
struct ext2_inode_info {int i_flags; int i_block_group; int /*<<< orphan*/  i_state; scalar_t__ i_dir_start_lookup; int /*<<< orphan*/ * i_block_alloc_info; scalar_t__ i_dtime; scalar_t__ i_dir_acl; scalar_t__ i_file_acl; scalar_t__ i_frag_size; scalar_t__ i_frag_no; scalar_t__ i_faddr; int /*<<< orphan*/  i_data; } ;
struct ext2_group_desc {int /*<<< orphan*/  bg_used_dirs_count; int /*<<< orphan*/  bg_free_inodes_count; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  scalar_t__ ino_t ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int ENOSPC ; 
 struct inode* ERR_PTR (int) ; 
 scalar_t__ EXT2_FIRST_INO (struct super_block*) ; 
 int EXT2_FL_INHERITED ; 
 struct ext2_inode_info* EXT2_I (struct inode*) ; 
 int EXT2_INODES_PER_GROUP (struct super_block*) ; 
 struct ext2_sb_info* EXT2_SB (struct super_block*) ; 
 int /*<<< orphan*/  EXT2_STATE_NEW ; 
 int /*<<< orphan*/  GRPID ; 
 int /*<<< orphan*/  OLDALLOC ; 
 int SB_SYNCHRONOUS ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_NOQUOTA ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 int /*<<< orphan*/  clear_nlink (struct inode*) ; 
 int /*<<< orphan*/  current_fsuid () ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  discard_new_inode (struct inode*) ; 
 int dquot_alloc_inode (struct inode*) ; 
 int /*<<< orphan*/  dquot_drop (struct inode*) ; 
 int /*<<< orphan*/  dquot_free_inode (struct inode*) ; 
 int dquot_initialize (struct inode*) ; 
 int /*<<< orphan*/  ext2_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  ext2_error (struct super_block*,char*,char*,unsigned long,...) ; 
 scalar_t__ ext2_find_next_zero_bit (unsigned long*,int,scalar_t__) ; 
 struct ext2_group_desc* ext2_get_group_desc (struct super_block*,int,struct buffer_head**) ; 
 int ext2_init_acl (struct inode*,struct inode*) ; 
 int ext2_init_security (struct inode*,struct inode*,struct qstr const*) ; 
 int ext2_mask_flags (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ext2_preread_inode (struct inode*) ; 
 scalar_t__ ext2_set_bit_atomic (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ext2_set_inode_flags (struct inode*) ; 
 int find_group_dir (struct super_block*,struct inode*) ; 
 int find_group_orlov (struct super_block*,struct inode*) ; 
 int find_group_other (struct super_block*,struct inode*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 
 scalar_t__ insert_inode_locked (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  le16_add_cpu (int /*<<< orphan*/ *,int) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  mark_buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct inode* new_inode (struct super_block*) ; 
 int /*<<< orphan*/  percpu_counter_add (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  percpu_counter_inc (int /*<<< orphan*/ *) ; 
 struct buffer_head* read_inode_bitmap (struct super_block*,int) ; 
 int /*<<< orphan*/ * sb_bgl_lock (struct ext2_sb_info*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sync_dirty_buffer (struct buffer_head*) ; 
 scalar_t__ test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

struct inode *ext2_new_inode(struct inode *dir, umode_t mode,
			     const struct qstr *qstr)
{
	struct super_block *sb;
	struct buffer_head *bitmap_bh = NULL;
	struct buffer_head *bh2;
	int group, i;
	ino_t ino = 0;
	struct inode * inode;
	struct ext2_group_desc *gdp;
	struct ext2_super_block *es;
	struct ext2_inode_info *ei;
	struct ext2_sb_info *sbi;
	int err;

	sb = dir->i_sb;
	inode = new_inode(sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	ei = EXT2_I(inode);
	sbi = EXT2_SB(sb);
	es = sbi->s_es;
	if (S_ISDIR(mode)) {
		if (test_opt(sb, OLDALLOC))
			group = find_group_dir(sb, dir);
		else
			group = find_group_orlov(sb, dir);
	} else 
		group = find_group_other(sb, dir);

	if (group == -1) {
		err = -ENOSPC;
		goto fail;
	}

	for (i = 0; i < sbi->s_groups_count; i++) {
		gdp = ext2_get_group_desc(sb, group, &bh2);
		if (!gdp) {
			if (++group == sbi->s_groups_count)
				group = 0;
			continue;
		}
		brelse(bitmap_bh);
		bitmap_bh = read_inode_bitmap(sb, group);
		if (!bitmap_bh) {
			err = -EIO;
			goto fail;
		}
		ino = 0;

repeat_in_this_group:
		ino = ext2_find_next_zero_bit((unsigned long *)bitmap_bh->b_data,
					      EXT2_INODES_PER_GROUP(sb), ino);
		if (ino >= EXT2_INODES_PER_GROUP(sb)) {
			/*
			 * Rare race: find_group_xx() decided that there were
			 * free inodes in this group, but by the time we tried
			 * to allocate one, they're all gone.  This can also
			 * occur because the counters which find_group_orlov()
			 * uses are approximate.  So just go and search the
			 * next block group.
			 */
			if (++group == sbi->s_groups_count)
				group = 0;
			continue;
		}
		if (ext2_set_bit_atomic(sb_bgl_lock(sbi, group),
						ino, bitmap_bh->b_data)) {
			/* we lost this inode */
			if (++ino >= EXT2_INODES_PER_GROUP(sb)) {
				/* this group is exhausted, try next group */
				if (++group == sbi->s_groups_count)
					group = 0;
				continue;
			}
			/* try to find free inode in the same group */
			goto repeat_in_this_group;
		}
		goto got;
	}

	/*
	 * Scanned all blockgroups.
	 */
	brelse(bitmap_bh);
	err = -ENOSPC;
	goto fail;
got:
	mark_buffer_dirty(bitmap_bh);
	if (sb->s_flags & SB_SYNCHRONOUS)
		sync_dirty_buffer(bitmap_bh);
	brelse(bitmap_bh);

	ino += group * EXT2_INODES_PER_GROUP(sb) + 1;
	if (ino < EXT2_FIRST_INO(sb) || ino > le32_to_cpu(es->s_inodes_count)) {
		ext2_error (sb, "ext2_new_inode",
			    "reserved inode or inode > inodes count - "
			    "block_group = %d,inode=%lu", group,
			    (unsigned long) ino);
		err = -EIO;
		goto fail;
	}

	percpu_counter_add(&sbi->s_freeinodes_counter, -1);
	if (S_ISDIR(mode))
		percpu_counter_inc(&sbi->s_dirs_counter);

	spin_lock(sb_bgl_lock(sbi, group));
	le16_add_cpu(&gdp->bg_free_inodes_count, -1);
	if (S_ISDIR(mode)) {
		if (sbi->s_debts[group] < 255)
			sbi->s_debts[group]++;
		le16_add_cpu(&gdp->bg_used_dirs_count, 1);
	} else {
		if (sbi->s_debts[group])
			sbi->s_debts[group]--;
	}
	spin_unlock(sb_bgl_lock(sbi, group));

	mark_buffer_dirty(bh2);
	if (test_opt(sb, GRPID)) {
		inode->i_mode = mode;
		inode->i_uid = current_fsuid();
		inode->i_gid = dir->i_gid;
	} else
		inode_init_owner(inode, dir, mode);

	inode->i_ino = ino;
	inode->i_blocks = 0;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	memset(ei->i_data, 0, sizeof(ei->i_data));
	ei->i_flags =
		ext2_mask_flags(mode, EXT2_I(dir)->i_flags & EXT2_FL_INHERITED);
	ei->i_faddr = 0;
	ei->i_frag_no = 0;
	ei->i_frag_size = 0;
	ei->i_file_acl = 0;
	ei->i_dir_acl = 0;
	ei->i_dtime = 0;
	ei->i_block_alloc_info = NULL;
	ei->i_block_group = group;
	ei->i_dir_start_lookup = 0;
	ei->i_state = EXT2_STATE_NEW;
	ext2_set_inode_flags(inode);
	spin_lock(&sbi->s_next_gen_lock);
	inode->i_generation = sbi->s_next_generation++;
	spin_unlock(&sbi->s_next_gen_lock);
	if (insert_inode_locked(inode) < 0) {
		ext2_error(sb, "ext2_new_inode",
			   "inode number already in use - inode=%lu",
			   (unsigned long) ino);
		err = -EIO;
		goto fail;
	}

	err = dquot_initialize(inode);
	if (err)
		goto fail_drop;

	err = dquot_alloc_inode(inode);
	if (err)
		goto fail_drop;

	err = ext2_init_acl(inode, dir);
	if (err)
		goto fail_free_drop;

	err = ext2_init_security(inode, dir, qstr);
	if (err)
		goto fail_free_drop;

	mark_inode_dirty(inode);
	ext2_debug("allocating inode %lu\n", inode->i_ino);
	ext2_preread_inode(inode);
	return inode;

fail_free_drop:
	dquot_free_inode(inode);

fail_drop:
	dquot_drop(inode);
	inode->i_flags |= S_NOQUOTA;
	clear_nlink(inode);
	discard_new_inode(inode);
	return ERR_PTR(err);

fail:
	make_bad_inode(inode);
	iput(inode);
	return ERR_PTR(err);
}