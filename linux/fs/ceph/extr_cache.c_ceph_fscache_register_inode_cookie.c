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
struct TYPE_2__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {TYPE_1__ i_mtime; int /*<<< orphan*/  i_mode; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_vino; scalar_t__ fscache; int /*<<< orphan*/  i_version; } ;
struct ceph_fs_client {int /*<<< orphan*/  fscache; } ;
struct ceph_aux_inode {int /*<<< orphan*/  mtime_nsec; int /*<<< orphan*/  mtime_sec; int /*<<< orphan*/  version; } ;
typedef  int /*<<< orphan*/  aux ;

/* Variables and functions */
 int /*<<< orphan*/  I_MUTEX_CHILD ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_fscache_inode_object_def ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 scalar_t__ fscache_acquire_cookie (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,struct ceph_aux_inode*,int,struct ceph_inode_info*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  i_size_read (struct inode*) ; 
 int /*<<< orphan*/  inode_lock_nested (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_unlock (struct inode*) ; 
 int /*<<< orphan*/  memset (struct ceph_aux_inode*,int /*<<< orphan*/ ,int) ; 

void ceph_fscache_register_inode_cookie(struct inode *inode)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	struct ceph_aux_inode aux;

	/* No caching for filesystem */
	if (!fsc->fscache)
		return;

	/* Only cache for regular files that are read only */
	if (!S_ISREG(inode->i_mode))
		return;

	inode_lock_nested(inode, I_MUTEX_CHILD);
	if (!ci->fscache) {
		memset(&aux, 0, sizeof(aux));
		aux.version = ci->i_version;
		aux.mtime_sec = inode->i_mtime.tv_sec;
		aux.mtime_nsec = inode->i_mtime.tv_nsec;
		ci->fscache = fscache_acquire_cookie(fsc->fscache,
						     &ceph_fscache_inode_object_def,
						     &ci->i_vino, sizeof(ci->i_vino),
						     &aux, sizeof(aux),
						     ci, i_size_read(inode), false);
	}
	inode_unlock(inode);
}