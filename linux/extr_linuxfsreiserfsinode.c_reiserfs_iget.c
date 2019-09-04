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
struct reiserfs_iget_args {int /*<<< orphan*/  dirid; int /*<<< orphan*/  objectid; } ;
struct inode {int i_state; } ;
struct TYPE_2__ {int /*<<< orphan*/  k_objectid; int /*<<< orphan*/  k_dir_id; } ;
struct cpu_key {TYPE_1__ on_disk_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INODE_PKEY (struct inode*) ; 
 int I_NEW ; 
 scalar_t__ comp_short_keys (int /*<<< orphan*/ ,struct cpu_key const*) ; 
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 
 int /*<<< orphan*/  reiserfs_find_actor ; 
 int /*<<< orphan*/  reiserfs_init_locked_inode ; 
 int /*<<< orphan*/  reiserfs_read_locked_inode (struct inode*,struct reiserfs_iget_args*) ; 
 int /*<<< orphan*/  reiserfs_write_lock_nested (struct super_block*,int) ; 
 int reiserfs_write_unlock_nested (struct super_block*) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *reiserfs_iget(struct super_block *s, const struct cpu_key *key)
{
	struct inode *inode;
	struct reiserfs_iget_args args;
	int depth;

	args.objectid = key->on_disk_key.k_objectid;
	args.dirid = key->on_disk_key.k_dir_id;
	depth = reiserfs_write_unlock_nested(s);
	inode = iget5_locked(s, key->on_disk_key.k_objectid,
			     reiserfs_find_actor, reiserfs_init_locked_inode,
			     (void *)(&args));
	reiserfs_write_lock_nested(s, depth);
	if (!inode)
		return ERR_PTR(-ENOMEM);

	if (inode->i_state & I_NEW) {
		reiserfs_read_locked_inode(inode, &args);
		unlock_new_inode(inode);
	}

	if (comp_short_keys(INODE_PKEY(inode), key) || is_bad_inode(inode)) {
		/* either due to i/o error or a stale NFS handle */
		iput(inode);
		inode = NULL;
	}
	return inode;
}