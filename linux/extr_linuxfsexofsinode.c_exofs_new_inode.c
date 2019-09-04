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
struct super_block {struct exofs_sb_info* s_fs_info; } ;
struct ore_io_state {struct inode* private; int /*<<< orphan*/  done; } ;
struct inode {scalar_t__ i_generation; scalar_t__ i_size; int /*<<< orphan*/  i_ctime; int /*<<< orphan*/  i_atime; int /*<<< orphan*/  i_mtime; int /*<<< orphan*/  i_blkbits; scalar_t__ i_ino; struct super_block* i_sb; } ;
struct exofs_sb_info {int /*<<< orphan*/  s_curr_pending; int /*<<< orphan*/  layout; int /*<<< orphan*/  s_next_gen_lock; int /*<<< orphan*/  s_next_generation; int /*<<< orphan*/  s_nextid; } ;
struct exofs_i_info {int /*<<< orphan*/  oc; int /*<<< orphan*/  one_comp; scalar_t__ i_commit_size; } ;

/* Variables and functions */
 int ENOMEM ; 
 struct inode* ERR_PTR (int) ; 
 int /*<<< orphan*/  EXOFS_BLKSHIFT ; 
 int /*<<< orphan*/  EXOFS_ERR (char*) ; 
 int /*<<< orphan*/  __oi_init (struct exofs_i_info*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_done ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 struct exofs_i_info* exofs_i (struct inode*) ; 
 int /*<<< orphan*/  exofs_init_comps (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct exofs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exofs_oi_objno (struct exofs_i_info*) ; 
 int /*<<< orphan*/  exofs_sbi_write_stats (struct exofs_sb_info*) ; 
 int /*<<< orphan*/  inode_init_owner (struct inode*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  insert_inode_hash (struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 struct inode* new_inode (struct super_block*) ; 
 int ore_create (struct ore_io_state*) ; 
 int ore_get_io_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct ore_io_state**) ; 
 int /*<<< orphan*/  ore_put_io_state (struct ore_io_state*) ; 
 int /*<<< orphan*/  set_obj_2bcreated (struct exofs_i_info*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

struct inode *exofs_new_inode(struct inode *dir, umode_t mode)
{
	struct super_block *sb = dir->i_sb;
	struct exofs_sb_info *sbi = sb->s_fs_info;
	struct inode *inode;
	struct exofs_i_info *oi;
	struct ore_io_state *ios;
	int ret;

	inode = new_inode(sb);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	oi = exofs_i(inode);
	__oi_init(oi);

	set_obj_2bcreated(oi);

	inode_init_owner(inode, dir, mode);
	inode->i_ino = sbi->s_nextid++;
	inode->i_blkbits = EXOFS_BLKSHIFT;
	inode->i_mtime = inode->i_atime = inode->i_ctime = current_time(inode);
	oi->i_commit_size = inode->i_size = 0;
	spin_lock(&sbi->s_next_gen_lock);
	inode->i_generation = sbi->s_next_generation++;
	spin_unlock(&sbi->s_next_gen_lock);
	insert_inode_hash(inode);

	exofs_init_comps(&oi->oc, &oi->one_comp, sb->s_fs_info,
			 exofs_oi_objno(oi));
	exofs_sbi_write_stats(sbi); /* Make sure new sbi->s_nextid is on disk */

	mark_inode_dirty(inode);

	ret = ore_get_io_state(&sbi->layout, &oi->oc, &ios);
	if (unlikely(ret)) {
		EXOFS_ERR("exofs_new_inode: ore_get_io_state failed\n");
		return ERR_PTR(ret);
	}

	ios->done = create_done;
	ios->private = inode;

	ret = ore_create(ios);
	if (ret) {
		ore_put_io_state(ios);
		return ERR_PTR(ret);
	}
	atomic_inc(&sbi->s_curr_pending);

	return inode;
}