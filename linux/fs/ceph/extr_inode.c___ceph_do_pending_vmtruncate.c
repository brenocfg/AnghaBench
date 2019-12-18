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
typedef  scalar_t__ u64 ;
struct inode {TYPE_1__* i_sb; int /*<<< orphan*/  i_data; } ;
struct ceph_inode_info {scalar_t__ i_truncate_pending; int i_wrbuffer_ref_head; int i_wrbuffer_ref; scalar_t__ i_truncate_size; int /*<<< orphan*/  i_cap_wq; int /*<<< orphan*/  i_truncate_mutex; int /*<<< orphan*/  i_ceph_lock; scalar_t__ i_wr_ref; scalar_t__ i_rd_ref; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_maxbytes; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CAPS_AUTHONLY ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  ceph_check_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,...) ; 
 int /*<<< orphan*/  filemap_write_and_wait_range (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  truncate_pagecache (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void __ceph_do_pending_vmtruncate(struct inode *inode)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	u64 to;
	int wrbuffer_refs, finish = 0;

	mutex_lock(&ci->i_truncate_mutex);
retry:
	spin_lock(&ci->i_ceph_lock);
	if (ci->i_truncate_pending == 0) {
		dout("__do_pending_vmtruncate %p none pending\n", inode);
		spin_unlock(&ci->i_ceph_lock);
		mutex_unlock(&ci->i_truncate_mutex);
		return;
	}

	/*
	 * make sure any dirty snapped pages are flushed before we
	 * possibly truncate them.. so write AND block!
	 */
	if (ci->i_wrbuffer_ref_head < ci->i_wrbuffer_ref) {
		spin_unlock(&ci->i_ceph_lock);
		dout("__do_pending_vmtruncate %p flushing snaps first\n",
		     inode);
		filemap_write_and_wait_range(&inode->i_data, 0,
					     inode->i_sb->s_maxbytes);
		goto retry;
	}

	/* there should be no reader or writer */
	WARN_ON_ONCE(ci->i_rd_ref || ci->i_wr_ref);

	to = ci->i_truncate_size;
	wrbuffer_refs = ci->i_wrbuffer_ref;
	dout("__do_pending_vmtruncate %p (%d) to %lld\n", inode,
	     ci->i_truncate_pending, to);
	spin_unlock(&ci->i_ceph_lock);

	truncate_pagecache(inode, to);

	spin_lock(&ci->i_ceph_lock);
	if (to == ci->i_truncate_size) {
		ci->i_truncate_pending = 0;
		finish = 1;
	}
	spin_unlock(&ci->i_ceph_lock);
	if (!finish)
		goto retry;

	mutex_unlock(&ci->i_truncate_mutex);

	if (wrbuffer_refs == 0)
		ceph_check_caps(ci, CHECK_CAPS_AUTHONLY, NULL);

	wake_up_all(&ci->i_cap_wq);
}