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
typedef  scalar_t__ u32 ;
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct ceph_inode_info {scalar_t__ i_rdcache_gen; scalar_t__ i_rdcache_revoking; int /*<<< orphan*/  i_truncate_mutex; int /*<<< orphan*/  i_ceph_lock; } ;
struct ceph_fs_client {int /*<<< orphan*/  mount_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_FILE_CACHE ; 
 scalar_t__ CEPH_MOUNT_SHUTDOWN ; 
 int /*<<< orphan*/  EIO ; 
 scalar_t__ READ_ONCE (int /*<<< orphan*/ ) ; 
 scalar_t__ __ceph_caps_revoking_other (struct ceph_inode_info*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_check_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_ino (struct inode*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_fs_client* ceph_inode_to_client (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,scalar_t__,...) ; 
 scalar_t__ invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mapping_set_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*,struct inode*) ; 
 int /*<<< orphan*/  pr_warn_ratelimited (char*,struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ceph_do_invalidate_pages(struct inode *inode)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	struct ceph_fs_client *fsc = ceph_inode_to_client(inode);
	u32 orig_gen;
	int check = 0;

	mutex_lock(&ci->i_truncate_mutex);

	if (READ_ONCE(fsc->mount_state) == CEPH_MOUNT_SHUTDOWN) {
		pr_warn_ratelimited("invalidate_pages %p %lld forced umount\n",
				    inode, ceph_ino(inode));
		mapping_set_error(inode->i_mapping, -EIO);
		truncate_pagecache(inode, 0);
		mutex_unlock(&ci->i_truncate_mutex);
		goto out;
	}

	spin_lock(&ci->i_ceph_lock);
	dout("invalidate_pages %p gen %d revoking %d\n", inode,
	     ci->i_rdcache_gen, ci->i_rdcache_revoking);
	if (ci->i_rdcache_revoking != ci->i_rdcache_gen) {
		if (__ceph_caps_revoking_other(ci, NULL, CEPH_CAP_FILE_CACHE))
			check = 1;
		spin_unlock(&ci->i_ceph_lock);
		mutex_unlock(&ci->i_truncate_mutex);
		goto out;
	}
	orig_gen = ci->i_rdcache_gen;
	spin_unlock(&ci->i_ceph_lock);

	if (invalidate_inode_pages2(inode->i_mapping) < 0) {
		pr_err("invalidate_pages %p fails\n", inode);
	}

	spin_lock(&ci->i_ceph_lock);
	if (orig_gen == ci->i_rdcache_gen &&
	    orig_gen == ci->i_rdcache_revoking) {
		dout("invalidate_pages %p gen %d successful\n", inode,
		     ci->i_rdcache_gen);
		ci->i_rdcache_revoking--;
		check = 1;
	} else {
		dout("invalidate_pages %p gen %d raced, now %d revoking %d\n",
		     inode, orig_gen, ci->i_rdcache_gen,
		     ci->i_rdcache_revoking);
		if (__ceph_caps_revoking_other(ci, NULL, CEPH_CAP_FILE_CACHE))
			check = 1;
	}
	spin_unlock(&ci->i_ceph_lock);
	mutex_unlock(&ci->i_truncate_mutex);
out:
	if (check)
		ceph_check_caps(ci, 0, NULL);
}