#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_13__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {scalar_t__ i_mode; scalar_t__ i_size; TYPE_3__ i_ctime; TYPE_4__ i_mtime; int /*<<< orphan*/  i_blocks; TYPE_4__ i_atime; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; int /*<<< orphan*/  i_sb; } ;
struct iattr {unsigned int ia_valid; scalar_t__ ia_mode; scalar_t__ ia_size; TYPE_3__ ia_ctime; TYPE_4__ ia_mtime; TYPE_4__ ia_atime; int /*<<< orphan*/  ia_gid; int /*<<< orphan*/  ia_uid; } ;
struct TYPE_10__ {void* mask; int /*<<< orphan*/  mtime; void* old_size; void* size; int /*<<< orphan*/  atime; void* mode; void* gid; void* uid; } ;
struct TYPE_11__ {TYPE_1__ setattr; } ;
struct ceph_mds_request {int r_inode_drop; int r_num_caps; TYPE_3__ r_stamp; TYPE_2__ r_args; struct inode* r_inode; } ;
struct ceph_mds_client {int /*<<< orphan*/  snap_rwsem; } ;
struct ceph_inode_info {scalar_t__ i_reported_size; int /*<<< orphan*/  i_ceph_lock; int /*<<< orphan*/  i_time_warp_seq; int /*<<< orphan*/  i_head_snapc; } ;
struct ceph_cap_flush {int dummy; } ;
struct TYPE_14__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 unsigned int ATTR_ATIME ; 
 unsigned int ATTR_CTIME ; 
 unsigned int ATTR_FILE ; 
 unsigned int ATTR_GID ; 
 unsigned int ATTR_MODE ; 
 unsigned int ATTR_MTIME ; 
 unsigned int ATTR_SIZE ; 
 unsigned int ATTR_UID ; 
 int CEPH_CAP_ANY_EXCL ; 
 int CEPH_CAP_AUTH_EXCL ; 
 int CEPH_CAP_AUTH_SHARED ; 
 int CEPH_CAP_FILE_EXCL ; 
 int CEPH_CAP_FILE_RD ; 
 int CEPH_CAP_FILE_SHARED ; 
 int CEPH_CAP_FILE_WR ; 
 int CEPH_CAP_XATTR_EXCL ; 
 int /*<<< orphan*/  CEPH_MDS_OP_SETATTR ; 
 int CEPH_SETATTR_ATIME ; 
 int CEPH_SETATTR_CTIME ; 
 int CEPH_SETATTR_GID ; 
 int CEPH_SETATTR_MODE ; 
 int CEPH_SETATTR_MTIME ; 
 int CEPH_SETATTR_SIZE ; 
 int CEPH_SETATTR_UID ; 
 int ENOMEM ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int PTR_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  USE_AUTH_MDS ; 
 int __ceph_caps_issued (struct ceph_inode_info*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __ceph_do_pending_vmtruncate (struct inode*) ; 
 int __ceph_mark_dirty_caps (struct ceph_inode_info*,int,struct ceph_cap_flush**) ; 
 int /*<<< orphan*/  __mark_inode_dirty (struct inode*,int) ; 
 int /*<<< orphan*/  calc_inode_blocks (scalar_t__) ; 
 struct ceph_cap_flush* ceph_alloc_cap_flush () ; 
 int /*<<< orphan*/  ceph_cap_string (int) ; 
 int /*<<< orphan*/  ceph_encode_timespec64 (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ceph_free_cap_flush (struct ceph_cap_flush*) ; 
 struct ceph_inode_info* ceph_inode (struct inode*) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,int /*<<< orphan*/ *,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 TYPE_8__* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 void* cpu_to_le32 (int) ; 
 void* cpu_to_le64 (scalar_t__) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,...) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_read_trylock (int /*<<< orphan*/ *) ; 
 int from_kgid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int from_kuid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  init_user_ns ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ timespec64_compare (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  timespec64_equal (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  uid_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

int __ceph_setattr(struct inode *inode, struct iattr *attr)
{
	struct ceph_inode_info *ci = ceph_inode(inode);
	unsigned int ia_valid = attr->ia_valid;
	struct ceph_mds_request *req;
	struct ceph_mds_client *mdsc = ceph_sb_to_client(inode->i_sb)->mdsc;
	struct ceph_cap_flush *prealloc_cf;
	int issued;
	int release = 0, dirtied = 0;
	int mask = 0;
	int err = 0;
	int inode_dirty_flags = 0;
	bool lock_snap_rwsem = false;

	prealloc_cf = ceph_alloc_cap_flush();
	if (!prealloc_cf)
		return -ENOMEM;

	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SETATTR,
				       USE_AUTH_MDS);
	if (IS_ERR(req)) {
		ceph_free_cap_flush(prealloc_cf);
		return PTR_ERR(req);
	}

	spin_lock(&ci->i_ceph_lock);
	issued = __ceph_caps_issued(ci, NULL);

	if (!ci->i_head_snapc &&
	    (issued & (CEPH_CAP_ANY_EXCL | CEPH_CAP_FILE_WR))) {
		lock_snap_rwsem = true;
		if (!down_read_trylock(&mdsc->snap_rwsem)) {
			spin_unlock(&ci->i_ceph_lock);
			down_read(&mdsc->snap_rwsem);
			spin_lock(&ci->i_ceph_lock);
			issued = __ceph_caps_issued(ci, NULL);
		}
	}

	dout("setattr %p issued %s\n", inode, ceph_cap_string(issued));

	if (ia_valid & ATTR_UID) {
		dout("setattr %p uid %d -> %d\n", inode,
		     from_kuid(&init_user_ns, inode->i_uid),
		     from_kuid(&init_user_ns, attr->ia_uid));
		if (issued & CEPH_CAP_AUTH_EXCL) {
			inode->i_uid = attr->ia_uid;
			dirtied |= CEPH_CAP_AUTH_EXCL;
		} else if ((issued & CEPH_CAP_AUTH_SHARED) == 0 ||
			   !uid_eq(attr->ia_uid, inode->i_uid)) {
			req->r_args.setattr.uid = cpu_to_le32(
				from_kuid(&init_user_ns, attr->ia_uid));
			mask |= CEPH_SETATTR_UID;
			release |= CEPH_CAP_AUTH_SHARED;
		}
	}
	if (ia_valid & ATTR_GID) {
		dout("setattr %p gid %d -> %d\n", inode,
		     from_kgid(&init_user_ns, inode->i_gid),
		     from_kgid(&init_user_ns, attr->ia_gid));
		if (issued & CEPH_CAP_AUTH_EXCL) {
			inode->i_gid = attr->ia_gid;
			dirtied |= CEPH_CAP_AUTH_EXCL;
		} else if ((issued & CEPH_CAP_AUTH_SHARED) == 0 ||
			   !gid_eq(attr->ia_gid, inode->i_gid)) {
			req->r_args.setattr.gid = cpu_to_le32(
				from_kgid(&init_user_ns, attr->ia_gid));
			mask |= CEPH_SETATTR_GID;
			release |= CEPH_CAP_AUTH_SHARED;
		}
	}
	if (ia_valid & ATTR_MODE) {
		dout("setattr %p mode 0%o -> 0%o\n", inode, inode->i_mode,
		     attr->ia_mode);
		if (issued & CEPH_CAP_AUTH_EXCL) {
			inode->i_mode = attr->ia_mode;
			dirtied |= CEPH_CAP_AUTH_EXCL;
		} else if ((issued & CEPH_CAP_AUTH_SHARED) == 0 ||
			   attr->ia_mode != inode->i_mode) {
			inode->i_mode = attr->ia_mode;
			req->r_args.setattr.mode = cpu_to_le32(attr->ia_mode);
			mask |= CEPH_SETATTR_MODE;
			release |= CEPH_CAP_AUTH_SHARED;
		}
	}

	if (ia_valid & ATTR_ATIME) {
		dout("setattr %p atime %lld.%ld -> %lld.%ld\n", inode,
		     inode->i_atime.tv_sec, inode->i_atime.tv_nsec,
		     attr->ia_atime.tv_sec, attr->ia_atime.tv_nsec);
		if (issued & CEPH_CAP_FILE_EXCL) {
			ci->i_time_warp_seq++;
			inode->i_atime = attr->ia_atime;
			dirtied |= CEPH_CAP_FILE_EXCL;
		} else if ((issued & CEPH_CAP_FILE_WR) &&
			   timespec64_compare(&inode->i_atime,
					    &attr->ia_atime) < 0) {
			inode->i_atime = attr->ia_atime;
			dirtied |= CEPH_CAP_FILE_WR;
		} else if ((issued & CEPH_CAP_FILE_SHARED) == 0 ||
			   !timespec64_equal(&inode->i_atime, &attr->ia_atime)) {
			ceph_encode_timespec64(&req->r_args.setattr.atime,
					       &attr->ia_atime);
			mask |= CEPH_SETATTR_ATIME;
			release |= CEPH_CAP_FILE_SHARED |
				   CEPH_CAP_FILE_RD | CEPH_CAP_FILE_WR;
		}
	}
	if (ia_valid & ATTR_SIZE) {
		dout("setattr %p size %lld -> %lld\n", inode,
		     inode->i_size, attr->ia_size);
		if ((issued & CEPH_CAP_FILE_EXCL) &&
		    attr->ia_size > inode->i_size) {
			i_size_write(inode, attr->ia_size);
			inode->i_blocks = calc_inode_blocks(attr->ia_size);
			ci->i_reported_size = attr->ia_size;
			dirtied |= CEPH_CAP_FILE_EXCL;
			ia_valid |= ATTR_MTIME;
		} else if ((issued & CEPH_CAP_FILE_SHARED) == 0 ||
			   attr->ia_size != inode->i_size) {
			req->r_args.setattr.size = cpu_to_le64(attr->ia_size);
			req->r_args.setattr.old_size =
				cpu_to_le64(inode->i_size);
			mask |= CEPH_SETATTR_SIZE;
			release |= CEPH_CAP_FILE_SHARED | CEPH_CAP_FILE_EXCL |
				   CEPH_CAP_FILE_RD | CEPH_CAP_FILE_WR;
		}
	}
	if (ia_valid & ATTR_MTIME) {
		dout("setattr %p mtime %lld.%ld -> %lld.%ld\n", inode,
		     inode->i_mtime.tv_sec, inode->i_mtime.tv_nsec,
		     attr->ia_mtime.tv_sec, attr->ia_mtime.tv_nsec);
		if (issued & CEPH_CAP_FILE_EXCL) {
			ci->i_time_warp_seq++;
			inode->i_mtime = attr->ia_mtime;
			dirtied |= CEPH_CAP_FILE_EXCL;
		} else if ((issued & CEPH_CAP_FILE_WR) &&
			   timespec64_compare(&inode->i_mtime,
					    &attr->ia_mtime) < 0) {
			inode->i_mtime = attr->ia_mtime;
			dirtied |= CEPH_CAP_FILE_WR;
		} else if ((issued & CEPH_CAP_FILE_SHARED) == 0 ||
			   !timespec64_equal(&inode->i_mtime, &attr->ia_mtime)) {
			ceph_encode_timespec64(&req->r_args.setattr.mtime,
					       &attr->ia_mtime);
			mask |= CEPH_SETATTR_MTIME;
			release |= CEPH_CAP_FILE_SHARED |
				   CEPH_CAP_FILE_RD | CEPH_CAP_FILE_WR;
		}
	}

	/* these do nothing */
	if (ia_valid & ATTR_CTIME) {
		bool only = (ia_valid & (ATTR_SIZE|ATTR_MTIME|ATTR_ATIME|
					 ATTR_MODE|ATTR_UID|ATTR_GID)) == 0;
		dout("setattr %p ctime %lld.%ld -> %lld.%ld (%s)\n", inode,
		     inode->i_ctime.tv_sec, inode->i_ctime.tv_nsec,
		     attr->ia_ctime.tv_sec, attr->ia_ctime.tv_nsec,
		     only ? "ctime only" : "ignored");
		if (only) {
			/*
			 * if kernel wants to dirty ctime but nothing else,
			 * we need to choose a cap to dirty under, or do
			 * a almost-no-op setattr
			 */
			if (issued & CEPH_CAP_AUTH_EXCL)
				dirtied |= CEPH_CAP_AUTH_EXCL;
			else if (issued & CEPH_CAP_FILE_EXCL)
				dirtied |= CEPH_CAP_FILE_EXCL;
			else if (issued & CEPH_CAP_XATTR_EXCL)
				dirtied |= CEPH_CAP_XATTR_EXCL;
			else
				mask |= CEPH_SETATTR_CTIME;
		}
	}
	if (ia_valid & ATTR_FILE)
		dout("setattr %p ATTR_FILE ... hrm!\n", inode);

	if (dirtied) {
		inode_dirty_flags = __ceph_mark_dirty_caps(ci, dirtied,
							   &prealloc_cf);
		inode->i_ctime = attr->ia_ctime;
	}

	release &= issued;
	spin_unlock(&ci->i_ceph_lock);
	if (lock_snap_rwsem)
		up_read(&mdsc->snap_rwsem);

	if (inode_dirty_flags)
		__mark_inode_dirty(inode, inode_dirty_flags);


	if (mask) {
		req->r_inode = inode;
		ihold(inode);
		req->r_inode_drop = release;
		req->r_args.setattr.mask = cpu_to_le32(mask);
		req->r_num_caps = 1;
		req->r_stamp = attr->ia_ctime;
		err = ceph_mdsc_do_request(mdsc, NULL, req);
	}
	dout("setattr %p result=%d (%s locally, %d remote)\n", inode, err,
	     ceph_cap_string(dirtied), mask);

	ceph_mdsc_put_request(req);
	ceph_free_cap_flush(prealloc_cf);

	if (err >= 0 && (mask & CEPH_SETATTR_SIZE))
		__ceph_do_pending_vmtruncate(inode);

	return err;
}