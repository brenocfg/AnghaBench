#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {struct afs_super_info* s_fs_info; } ;
struct TYPE_6__ {scalar_t__ tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int i_state; int i_mode; int /*<<< orphan*/  i_flags; scalar_t__ i_generation; scalar_t__ i_blocks; TYPE_3__ i_ctime; TYPE_3__ i_mtime; TYPE_3__ i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; scalar_t__ i_size; int /*<<< orphan*/  i_ino; } ;
struct afs_vnode {int /*<<< orphan*/  flags; } ;
struct afs_super_info {TYPE_1__* volume; } ;
struct TYPE_5__ {int vnode; int unique; int /*<<< orphan*/  vid; } ;
struct afs_iget_data {TYPE_2__ fid; TYPE_1__* volume; } ;
typedef  int /*<<< orphan*/  atomic_t ;
struct TYPE_4__ {int /*<<< orphan*/  vid; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  AFS_VNODE_MOUNTPOINT ; 
 int /*<<< orphan*/  AFS_VNODE_PSEUDODIR ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GLOBAL_ROOT_GID ; 
 int /*<<< orphan*/  GLOBAL_ROOT_UID ; 
 int I_NEW ; 
 int /*<<< orphan*/  S_AUTOMOUNT ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IXUGO ; 
 int /*<<< orphan*/  S_NOATIME ; 
 int /*<<< orphan*/  _debug (char*,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  afs_autocell_inode_operations ; 
 int /*<<< orphan*/  afs_dynroot_file_operations ; 
 int /*<<< orphan*/  afs_dynroot_inode_operations ; 
 int /*<<< orphan*/  afs_iget5_pseudo_dir_test ; 
 int /*<<< orphan*/  afs_iget5_set ; 
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_seconds () ; 
 struct inode* iget5_locked (struct super_block*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct afs_iget_data*) ; 
 int /*<<< orphan*/  inode_set_iversion_raw (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_nlink (struct inode*,int) ; 
 int /*<<< orphan*/  unlock_new_inode (struct inode*) ; 

struct inode *afs_iget_pseudo_dir(struct super_block *sb, bool root)
{
	struct afs_iget_data data;
	struct afs_super_info *as;
	struct afs_vnode *vnode;
	struct inode *inode;
	static atomic_t afs_autocell_ino;

	_enter("");

	as = sb->s_fs_info;
	if (as->volume) {
		data.volume = as->volume;
		data.fid.vid = as->volume->vid;
	}
	if (root) {
		data.fid.vnode = 1;
		data.fid.unique = 1;
	} else {
		data.fid.vnode = atomic_inc_return(&afs_autocell_ino);
		data.fid.unique = 0;
	}

	inode = iget5_locked(sb, data.fid.vnode,
			     afs_iget5_pseudo_dir_test, afs_iget5_set,
			     &data);
	if (!inode) {
		_leave(" = -ENOMEM");
		return ERR_PTR(-ENOMEM);
	}

	_debug("GOT INODE %p { ino=%lu, vl=%x, vn=%x, u=%x }",
	       inode, inode->i_ino, data.fid.vid, data.fid.vnode,
	       data.fid.unique);

	vnode = AFS_FS_I(inode);

	/* there shouldn't be an existing inode */
	BUG_ON(!(inode->i_state & I_NEW));

	inode->i_size		= 0;
	inode->i_mode		= S_IFDIR | S_IRUGO | S_IXUGO;
	if (root) {
		inode->i_op	= &afs_dynroot_inode_operations;
		inode->i_fop	= &afs_dynroot_file_operations;
	} else {
		inode->i_op	= &afs_autocell_inode_operations;
	}
	set_nlink(inode, 2);
	inode->i_uid		= GLOBAL_ROOT_UID;
	inode->i_gid		= GLOBAL_ROOT_GID;
	inode->i_ctime.tv_sec	= get_seconds();
	inode->i_ctime.tv_nsec	= 0;
	inode->i_atime		= inode->i_mtime = inode->i_ctime;
	inode->i_blocks		= 0;
	inode_set_iversion_raw(inode, 0);
	inode->i_generation	= 0;

	set_bit(AFS_VNODE_PSEUDODIR, &vnode->flags);
	if (!root) {
		set_bit(AFS_VNODE_MOUNTPOINT, &vnode->flags);
		inode->i_flags |= S_AUTOMOUNT;
	}

	inode->i_flags |= S_NOATIME;
	unlock_new_inode(inode);
	_leave(" = %p", inode);
	return inode;
}