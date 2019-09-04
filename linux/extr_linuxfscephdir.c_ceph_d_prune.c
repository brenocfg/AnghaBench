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
struct dentry {int /*<<< orphan*/  d_parent; } ;
struct TYPE_2__ {scalar_t__ snap; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_shared_gen; TYPE_1__ i_vino; } ;
struct ceph_dentry_info {scalar_t__ offset; scalar_t__ lease_shared_gen; } ;

/* Variables and functions */
 scalar_t__ CEPH_SNAPDIR ; 
 scalar_t__ IS_ROOT (struct dentry*) ; 
 int /*<<< orphan*/  __ceph_dir_clear_complete (struct ceph_inode_info*) ; 
 int /*<<< orphan*/  __ceph_dir_clear_ordered (struct ceph_inode_info*) ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 struct ceph_dentry_info* ceph_dentry (struct dentry*) ; 
 struct ceph_inode_info* ceph_inode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_inode (int /*<<< orphan*/ ) ; 
 scalar_t__ d_really_is_negative (struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,struct dentry*) ; 

__attribute__((used)) static void ceph_d_prune(struct dentry *dentry)
{
	struct ceph_inode_info *dir_ci;
	struct ceph_dentry_info *di;

	dout("ceph_d_prune %pd %p\n", dentry, dentry);

	/* do we have a valid parent? */
	if (IS_ROOT(dentry))
		return;

	/* we hold d_lock, so d_parent is stable */
	dir_ci = ceph_inode(d_inode(dentry->d_parent));
	if (dir_ci->i_vino.snap == CEPH_SNAPDIR)
		return;

	/* who calls d_delete() should also disable dcache readdir */
	if (d_really_is_negative(dentry))
		return;

	/* d_fsdata does not get cleared until d_release */
	if (!d_unhashed(dentry)) {
		__ceph_dir_clear_complete(dir_ci);
		return;
	}

	/* Disable dcache readdir just in case that someone called d_drop()
	 * or d_invalidate(), but MDS didn't revoke CEPH_CAP_FILE_SHARED
	 * properly (dcache readdir is still enabled) */
	di = ceph_dentry(dentry);
	if (di->offset > 0 &&
	    di->lease_shared_gen == atomic_read(&dir_ci->i_shared_gen))
		__ceph_dir_clear_ordered(dir_ci);
}