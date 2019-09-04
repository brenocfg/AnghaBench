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
struct key {int dummy; } ;
struct inode {int i_mode; scalar_t__ i_blocks; TYPE_1__* i_mapping; int /*<<< orphan*/ * i_op; int /*<<< orphan*/ * i_fop; int /*<<< orphan*/  i_flags; } ;
struct TYPE_4__ {int type; int mode; int /*<<< orphan*/  data_version; scalar_t__ size; int /*<<< orphan*/  nlink; } ;
struct afs_vnode {int /*<<< orphan*/  cb_lock; TYPE_2__ status; int /*<<< orphan*/  invalid_before; int /*<<< orphan*/  flags; } ;
struct TYPE_3__ {int /*<<< orphan*/ * a_ops; } ;

/* Variables and functions */
#define  AFS_FTYPE_DIR 130 
#define  AFS_FTYPE_FILE 129 
#define  AFS_FTYPE_SYMLINK 128 
 int /*<<< orphan*/  AFS_VNODE_MOUNTPOINT ; 
 int /*<<< orphan*/  AFS_VNODE_NOT_YET_SET ; 
 struct inode* AFS_VNODE_TO_I (struct afs_vnode*) ; 
 int /*<<< orphan*/  EBADMSG ; 
 int /*<<< orphan*/  S_AUTOMOUNT ; 
 int S_IFDIR ; 
 int S_IFLNK ; 
 int S_IFREG ; 
 int /*<<< orphan*/  _debug (char*,int,int /*<<< orphan*/ ,unsigned long long,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  afs_dir_aops ; 
 int /*<<< orphan*/  afs_dir_file_operations ; 
 int /*<<< orphan*/  afs_dir_inode_operations ; 
 int /*<<< orphan*/  afs_file_inode_operations ; 
 int /*<<< orphan*/  afs_file_operations ; 
 int /*<<< orphan*/  afs_fs_aops ; 
 int /*<<< orphan*/  afs_mntpt_file_operations ; 
 int /*<<< orphan*/  afs_mntpt_inode_operations ; 
 int afs_protocol_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  afs_symlink_inode_operations ; 
 int /*<<< orphan*/  afs_update_inode_from_status (struct afs_vnode*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_nohighmem (struct inode*) ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  read_seqlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_sequnlock_excl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_inode_init_from_status(struct afs_vnode *vnode, struct key *key)
{
	struct inode *inode = AFS_VNODE_TO_I(vnode);

	_debug("FS: ft=%d lk=%d sz=%llu ver=%Lu mod=%hu",
	       vnode->status.type,
	       vnode->status.nlink,
	       (unsigned long long) vnode->status.size,
	       vnode->status.data_version,
	       vnode->status.mode);

	read_seqlock_excl(&vnode->cb_lock);

	afs_update_inode_from_status(vnode, &vnode->status, NULL,
				     AFS_VNODE_NOT_YET_SET);

	switch (vnode->status.type) {
	case AFS_FTYPE_FILE:
		inode->i_mode	= S_IFREG | vnode->status.mode;
		inode->i_op	= &afs_file_inode_operations;
		inode->i_fop	= &afs_file_operations;
		inode->i_mapping->a_ops	= &afs_fs_aops;
		break;
	case AFS_FTYPE_DIR:
		inode->i_mode	= S_IFDIR | vnode->status.mode;
		inode->i_op	= &afs_dir_inode_operations;
		inode->i_fop	= &afs_dir_file_operations;
		inode->i_mapping->a_ops	= &afs_dir_aops;
		break;
	case AFS_FTYPE_SYMLINK:
		/* Symlinks with a mode of 0644 are actually mountpoints. */
		if ((vnode->status.mode & 0777) == 0644) {
			inode->i_flags |= S_AUTOMOUNT;

			set_bit(AFS_VNODE_MOUNTPOINT, &vnode->flags);

			inode->i_mode	= S_IFDIR | 0555;
			inode->i_op	= &afs_mntpt_inode_operations;
			inode->i_fop	= &afs_mntpt_file_operations;
			inode->i_mapping->a_ops	= &afs_fs_aops;
		} else {
			inode->i_mode	= S_IFLNK | vnode->status.mode;
			inode->i_op	= &afs_symlink_inode_operations;
			inode->i_mapping->a_ops	= &afs_fs_aops;
		}
		inode_nohighmem(inode);
		break;
	default:
		printk("kAFS: AFS vnode with undefined type\n");
		read_sequnlock_excl(&vnode->cb_lock);
		return afs_protocol_error(NULL, -EBADMSG);
	}

	inode->i_blocks		= 0;
	vnode->invalid_before	= vnode->status.data_version;

	read_sequnlock_excl(&vnode->cb_lock);
	return 0;
}