#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mr_lock; } ;
struct TYPE_6__ {int /*<<< orphan*/  di_size; int /*<<< orphan*/  di_gid; int /*<<< orphan*/  di_uid; } ;
struct inode {int /*<<< orphan*/  i_mapping; TYPE_3__* i_sb; int /*<<< orphan*/  i_rwsem; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_state; int /*<<< orphan*/  i_ino; } ;
struct xfs_inode {TYPE_5__ i_lock; TYPE_4__* i_mount; int /*<<< orphan*/  d_ops; TYPE_1__ i_d; int /*<<< orphan*/  i_ino; struct inode i_vnode; } ;
typedef  int gfp_t ;
struct TYPE_9__ {int /*<<< orphan*/  m_nondir_inode_ops; int /*<<< orphan*/  m_dir_inode_ops; } ;
struct TYPE_8__ {TYPE_2__* s_type; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mutex_dir_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  I_NEW ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_IFORK_Q (struct xfs_inode*) ; 
 int __GFP_FS ; 
 int /*<<< orphan*/  cache_no_acl (struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_fake_hash (struct inode*) ; 
 int /*<<< orphan*/  inode_has_no_xattr (struct inode*) ; 
 int /*<<< orphan*/  inode_sb_list_add (struct inode*) ; 
 int /*<<< orphan*/  lockdep_set_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int mapping_gfp_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_gfp_mask (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  xfs_diflags_to_iflags (struct inode*,struct xfs_inode*) ; 
 int /*<<< orphan*/  xfs_dir_ilock_class ; 
 int /*<<< orphan*/  xfs_gid_to_kgid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xfs_nondir_ilock_class ; 
 int /*<<< orphan*/  xfs_uid_to_kuid (int /*<<< orphan*/ ) ; 

void
xfs_setup_inode(
	struct xfs_inode	*ip)
{
	struct inode		*inode = &ip->i_vnode;
	gfp_t			gfp_mask;

	inode->i_ino = ip->i_ino;
	inode->i_state = I_NEW;

	inode_sb_list_add(inode);
	/* make the inode look hashed for the writeback code */
	inode_fake_hash(inode);

	inode->i_uid    = xfs_uid_to_kuid(ip->i_d.di_uid);
	inode->i_gid    = xfs_gid_to_kgid(ip->i_d.di_gid);

	i_size_write(inode, ip->i_d.di_size);
	xfs_diflags_to_iflags(inode, ip);

	if (S_ISDIR(inode->i_mode)) {
		/*
		 * We set the i_rwsem class here to avoid potential races with
		 * lockdep_annotate_inode_mutex_key() reinitialising the lock
		 * after a filehandle lookup has already found the inode in
		 * cache before it has been unlocked via unlock_new_inode().
		 */
		lockdep_set_class(&inode->i_rwsem,
				  &inode->i_sb->s_type->i_mutex_dir_key);
		lockdep_set_class(&ip->i_lock.mr_lock, &xfs_dir_ilock_class);
		ip->d_ops = ip->i_mount->m_dir_inode_ops;
	} else {
		ip->d_ops = ip->i_mount->m_nondir_inode_ops;
		lockdep_set_class(&ip->i_lock.mr_lock, &xfs_nondir_ilock_class);
	}

	/*
	 * Ensure all page cache allocations are done from GFP_NOFS context to
	 * prevent direct reclaim recursion back into the filesystem and blowing
	 * stacks or deadlocking.
	 */
	gfp_mask = mapping_gfp_mask(inode->i_mapping);
	mapping_set_gfp_mask(inode->i_mapping, (gfp_mask & ~(__GFP_FS)));

	/*
	 * If there is no attribute fork no ACL can exist on this inode,
	 * and it can't have any file capabilities attached to it either.
	 */
	if (!XFS_IFORK_Q(ip)) {
		inode_has_no_xattr(inode);
		cache_no_acl(inode);
	}
}