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
struct inode {int /*<<< orphan*/  i_mode; struct super_block* i_sb; } ;
struct fat_slot_info {int /*<<< orphan*/  bh; int /*<<< orphan*/  i_pos; int /*<<< orphan*/  de; } ;
struct dentry {scalar_t__ d_parent; int /*<<< orphan*/  d_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_lock; } ;

/* Variables and functions */
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 TYPE_1__* MSDOS_SB (struct super_block*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (int /*<<< orphan*/ ) ; 
 struct dentry* d_find_alias (struct inode*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 struct inode* fat_build_inode (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_query_iversion (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfat_d_version_set (struct dentry*,int /*<<< orphan*/ ) ; 
 int vfat_find (struct inode*,int /*<<< orphan*/ *,struct fat_slot_info*) ; 

__attribute__((used)) static struct dentry *vfat_lookup(struct inode *dir, struct dentry *dentry,
				  unsigned int flags)
{
	struct super_block *sb = dir->i_sb;
	struct fat_slot_info sinfo;
	struct inode *inode;
	struct dentry *alias;
	int err;

	mutex_lock(&MSDOS_SB(sb)->s_lock);

	err = vfat_find(dir, &dentry->d_name, &sinfo);
	if (err) {
		if (err == -ENOENT) {
			inode = NULL;
			goto out;
		}
		goto error;
	}

	inode = fat_build_inode(sb, sinfo.de, sinfo.i_pos);
	brelse(sinfo.bh);
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto error;
	}

	alias = d_find_alias(inode);
	/*
	 * Checking "alias->d_parent == dentry->d_parent" to make sure
	 * FS is not corrupted (especially double linked dir).
	 */
	if (alias && alias->d_parent == dentry->d_parent) {
		/*
		 * This inode has non anonymous-DCACHE_DISCONNECTED
		 * dentry. This means, the user did ->lookup() by an
		 * another name (longname vs 8.3 alias of it) in past.
		 *
		 * Switch to new one for reason of locality if possible.
		 */
		if (!S_ISDIR(inode->i_mode))
			d_move(alias, dentry);
		iput(inode);
		mutex_unlock(&MSDOS_SB(sb)->s_lock);
		return alias;
	} else
		dput(alias);

out:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	if (!inode)
		vfat_d_version_set(dentry, inode_query_iversion(dir));
	return d_splice_alias(inode, dentry);
error:
	mutex_unlock(&MSDOS_SB(sb)->s_lock);
	return ERR_PTR(err);
}