#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct reiserfs_dir_entry {int /*<<< orphan*/  de_dir_id; int /*<<< orphan*/ * de_gen_number_bit_string; } ;
struct inode {TYPE_2__* i_sb; int /*<<< orphan*/  i_flags; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct cpu_key {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  s_blocksize; } ;

/* Variables and functions */
 int /*<<< orphan*/  EACCES ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INITIALIZE_PATH (int /*<<< orphan*/ ) ; 
 int IO_ERROR ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ IS_PRIVATE (struct inode*) ; 
 int NAME_FOUND ; 
 scalar_t__ REISERFS_MAX_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_PRIVATE ; 
 struct dentry* d_splice_alias (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  path_to_entry ; 
 int /*<<< orphan*/  pathrelse (int /*<<< orphan*/ *) ; 
 int reiserfs_find_entry (struct inode*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct reiserfs_dir_entry*) ; 
 struct inode* reiserfs_iget (TYPE_2__*,struct cpu_key*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (TYPE_2__*) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (TYPE_2__*) ; 

__attribute__((used)) static struct dentry *reiserfs_lookup(struct inode *dir, struct dentry *dentry,
				      unsigned int flags)
{
	int retval;
	struct inode *inode = NULL;
	struct reiserfs_dir_entry de;
	INITIALIZE_PATH(path_to_entry);

	if (REISERFS_MAX_NAME(dir->i_sb->s_blocksize) < dentry->d_name.len)
		return ERR_PTR(-ENAMETOOLONG);

	reiserfs_write_lock(dir->i_sb);

	de.de_gen_number_bit_string = NULL;
	retval =
	    reiserfs_find_entry(dir, dentry->d_name.name, dentry->d_name.len,
				&path_to_entry, &de);
	pathrelse(&path_to_entry);
	if (retval == NAME_FOUND) {
		inode = reiserfs_iget(dir->i_sb,
				      (struct cpu_key *)&de.de_dir_id);
		if (!inode || IS_ERR(inode)) {
			reiserfs_write_unlock(dir->i_sb);
			return ERR_PTR(-EACCES);
		}

		/*
		 * Propagate the private flag so we know we're
		 * in the priv tree
		 */
		if (IS_PRIVATE(dir))
			inode->i_flags |= S_PRIVATE;
	}
	reiserfs_write_unlock(dir->i_sb);
	if (retval == IO_ERROR) {
		return ERR_PTR(-EIO);
	}

	return d_splice_alias(inode, dentry);
}