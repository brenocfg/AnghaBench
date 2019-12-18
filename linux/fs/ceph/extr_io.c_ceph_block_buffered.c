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
struct inode {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_rwsem; } ;
struct ceph_inode_info {int i_ceph_flags; int /*<<< orphan*/  i_ceph_lock; } ;

/* Variables and functions */
 int CEPH_I_ODIRECT ; 
 int READ_ONCE (int) ; 
 int /*<<< orphan*/  filemap_write_and_wait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lockdep_assert_held_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ceph_block_buffered(struct ceph_inode_info *ci, struct inode *inode)
{
	lockdep_assert_held_write(&inode->i_rwsem);

	if (!(READ_ONCE(ci->i_ceph_flags) & CEPH_I_ODIRECT)) {
		spin_lock(&ci->i_ceph_lock);
		ci->i_ceph_flags |= CEPH_I_ODIRECT;
		spin_unlock(&ci->i_ceph_lock);
		/* FIXME: unmap_mapping_range? */
		filemap_write_and_wait(inode->i_mapping);
	}
}