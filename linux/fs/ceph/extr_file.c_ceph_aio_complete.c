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
struct inode {int dummy; } ;
struct ceph_inode_info {int /*<<< orphan*/  i_ceph_lock; int /*<<< orphan*/  i_inline_version; } ;
struct ceph_aio_request {int error; int total_len; int /*<<< orphan*/  prealloc_cf; TYPE_1__* iocb; scalar_t__ write; int /*<<< orphan*/  pending_reqs; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {scalar_t__ ki_pos; int /*<<< orphan*/  (* ki_complete ) (TYPE_1__*,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_FILE_RD ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_WR ; 
 int /*<<< orphan*/  CEPH_INLINE_NONE ; 
 int /*<<< orphan*/  CHECK_CAPS_AUTHONLY ; 
 int __ceph_mark_dirty_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int) ; 
 int /*<<< orphan*/  atomic_dec_and_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_check_caps (struct ceph_inode_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ceph_free_cap_flush (int /*<<< orphan*/ ) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 scalar_t__ ceph_inode_set_size (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ceph_put_cap_refs (struct ceph_inode_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,int) ; 
 scalar_t__ i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ceph_aio_request*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ceph_aio_complete(struct inode *inode,
			      struct ceph_aio_request *aio_req)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	int ret;

	if (!atomic_dec_and_test(&aio_req->pending_reqs))
		return;

	ret = aio_req->error;
	if (!ret)
		ret = aio_req->total_len;

	dout("ceph_aio_complete %p rc %d\n", inode, ret);

	if (ret >= 0 && aio_req->write) {
		int dirty;

		loff_t endoff = aio_req->iocb->ki_pos + aio_req->total_len;
		if (endoff > i_size_read(inode)) {
			if (ceph_inode_set_size(inode, endoff))
				ceph_check_caps(ci, CHECK_CAPS_AUTHONLY, NULL);
		}

		spin_lock(&ci->i_ceph_lock);
		ci->i_inline_version = CEPH_INLINE_NONE;
		dirty = __ceph_mark_dirty_caps(ci, CEPH_CAP_FILE_WR,
					       &aio_req->prealloc_cf);
		spin_unlock(&ci->i_ceph_lock);
		if (dirty)
			__mark_inode_dirty(inode, dirty);

	}

	ceph_put_cap_refs(ci, (aio_req->write ? CEPH_CAP_FILE_WR :
						CEPH_CAP_FILE_RD));

	aio_req->iocb->ki_complete(aio_req->iocb, ret, 0);

	ceph_free_cap_flush(aio_req->prealloc_cf);
	kfree(aio_req);
}