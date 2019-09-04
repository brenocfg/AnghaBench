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
typedef  int /*<<< orphan*/  umode_t ;
typedef  scalar_t__ sysv_ino_t ;
struct writeback_control {int /*<<< orphan*/  sync_mode; } ;
struct sysv_sb_info {int /*<<< orphan*/  s_lock; int /*<<< orphan*/  s_sb_total_free_inodes; scalar_t__* s_sb_fic_count; } ;
struct super_block {int dummy; } ;
struct inode {scalar_t__ i_blocks; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; void* i_ino; struct super_block* i_sb; } ;
struct TYPE_2__ {scalar_t__ i_dir_start_lookup; int /*<<< orphan*/  i_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  ENOSPC ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 TYPE_1__* SYSV_I (struct inode*) ; 
 struct sysv_sb_info* SYSV_SB (struct super_block*) ; 
 int /*<<< orphan*/  WB_SYNC_NONE ; 
 scalar_t__ cpu_to_fs16 (struct sysv_sb_info*,unsigned int) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  dirty_sb (struct super_block*) ; 
 int /*<<< orphan*/  fs16_add (struct sysv_sb_info*,int /*<<< orphan*/ ,int) ; 
 void* fs16_to_cpu (struct sysv_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct inode* new_inode (struct super_block*) ; 
 unsigned int refill_free_cache (struct super_block*) ; 
 scalar_t__* sv_sb_fic_inode (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  sysv_write_inode (struct inode*,struct writeback_control*) ; 

struct inode * sysv_new_inode(const struct inode * dir, umode_t mode)
{
	struct super_block *sb = dir->i_sb;
	struct sysv_sb_info *sbi = SYSV_SB(sb);
	struct inode *inode;
	sysv_ino_t ino;
	unsigned count;
	struct writeback_control wbc = {
		.sync_mode = WB_SYNC_NONE
	};

	inode = new_inode(sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	mutex_lock(&sbi->s_lock);
	count = fs16_to_cpu(sbi, *sbi->s_sb_fic_count);
	if (count == 0 || (*sv_sb_fic_inode(sb,count-1) == 0)) {
		count = refill_free_cache(sb);
		if (count == 0) {
			iput(inode);
			mutex_unlock(&sbi->s_lock);
			return ERR_PTR(-ENOSPC);
		}
	}
	/* Now count > 0. */
	ino = *sv_sb_fic_inode(sb,--count);
	*sbi->s_sb_fic_count = cpu_to_fs16(sbi, count);
	fs16_add(sbi, sbi->s_sb_total_free_inodes, -1);
	dirty_sb(sb);
	inode_init_owner(inode, dir, mode);
	inode->i_ino = fs16_to_cpu(sbi, ino);
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	inode->i_blocks = 0;
	memset(SYSV_I(inode)->i_data, 0, sizeof(SYSV_I(inode)->i_data));
	SYSV_I(inode)->i_dir_start_lookup = 0;
	insert_inode_hash(inode);
	mark_inode_dirty(inode);

	sysv_write_inode(inode, &wbc);	/* ensure inode not allocated again */
	mark_inode_dirty(inode);	/* cleared by sysv_write_inode() */
	/* That's it. */
	mutex_unlock(&sbi->s_lock);
	return inode;
}