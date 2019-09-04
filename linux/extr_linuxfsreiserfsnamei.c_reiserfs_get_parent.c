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
struct reiserfs_dir_entry {int /*<<< orphan*/  de_dir_id; int /*<<< orphan*/ * de_gen_number_bit_string; } ;
struct inode {scalar_t__ i_nlink; int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct cpu_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INITIALIZE_PATH (int /*<<< orphan*/ ) ; 
 int NAME_FOUND ; 
 struct inode* d_inode (struct dentry*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 int /*<<< orphan*/  path_to_entry ; 
 int /*<<< orphan*/  pathrelse (int /*<<< orphan*/ *) ; 
 int reiserfs_find_entry (struct inode*,char*,int,int /*<<< orphan*/ *,struct reiserfs_dir_entry*) ; 
 struct inode* reiserfs_iget (int /*<<< orphan*/ ,struct cpu_key*) ; 
 int /*<<< orphan*/  reiserfs_write_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_write_unlock (int /*<<< orphan*/ ) ; 

struct dentry *reiserfs_get_parent(struct dentry *child)
{
	int retval;
	struct inode *inode = NULL;
	struct reiserfs_dir_entry de;
	INITIALIZE_PATH(path_to_entry);
	struct inode *dir = d_inode(child);

	if (dir->i_nlink == 0) {
		return ERR_PTR(-ENOENT);
	}
	de.de_gen_number_bit_string = NULL;

	reiserfs_write_lock(dir->i_sb);
	retval = reiserfs_find_entry(dir, "..", 2, &path_to_entry, &de);
	pathrelse(&path_to_entry);
	if (retval != NAME_FOUND) {
		reiserfs_write_unlock(dir->i_sb);
		return ERR_PTR(-ENOENT);
	}
	inode = reiserfs_iget(dir->i_sb, (struct cpu_key *)&de.de_dir_id);
	reiserfs_write_unlock(dir->i_sb);

	return d_obtain_alias(inode);
}