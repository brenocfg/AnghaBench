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
typedef  int /*<<< orphan*/  u32 ;
struct path {int /*<<< orphan*/  dentry; } ;
struct kstat {int size; int blksize; int nlink; scalar_t__ blocks; scalar_t__ dev; int /*<<< orphan*/  ino; } ;
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_ino; } ;
struct ceph_inode_info {int i_rbytes; int i_files; int i_subdirs; } ;

/* Variables and functions */
 scalar_t__ CEPH_NOSNAP ; 
 int /*<<< orphan*/  CEPH_STAT_CAP_INODE_ALL ; 
 int /*<<< orphan*/  RBYTES ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int ceph_do_getattr (struct inode*,int /*<<< orphan*/ ,int) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 scalar_t__ ceph_test_mount_opt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_translate_ino (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* d_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_fillattr (struct inode*,struct kstat*) ; 

int ceph_getattr(const struct path *path, struct kstat *stat,
		 u32 request_mask, unsigned int flags)
{
	struct inode *inode = d_inode(path->dentry);
	struct ceph_inode_info *ci = ceph_inode(inode);
	int err;

	err = ceph_do_getattr(inode, CEPH_STAT_CAP_INODE_ALL, false);
	if (!err) {
		generic_fillattr(inode, stat);
		stat->ino = ceph_translate_ino(inode->i_sb, inode->i_ino);
		if (ceph_snap(inode) != CEPH_NOSNAP)
			stat->dev = ceph_snap(inode);
		else
			stat->dev = 0;
		if (S_ISDIR(inode->i_mode)) {
			if (ceph_test_mount_opt(ceph_sb_to_client(inode->i_sb),
						RBYTES))
				stat->size = ci->i_rbytes;
			else
				stat->size = ci->i_files + ci->i_subdirs;
			stat->blocks = 0;
			stat->blksize = 65536;
			/*
			 * Some applications rely on the number of st_nlink
			 * value on directories to be either 0 (if unlinked)
			 * or 2 + number of subdirectories.
			 */
			if (stat->nlink == 1)
				/* '.' + '..' + subdirs */
				stat->nlink = 1 + 1 + ci->i_subdirs;
		}
	}
	return err;
}