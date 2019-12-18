#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  umode_t ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_8__ {TYPE_3__* head; } ;
struct TYPE_5__ {void* rdev; void* mode; } ;
struct TYPE_6__ {TYPE_1__ mknod; } ;
struct ceph_mds_request {int r_num_caps; int r_dentry_drop; TYPE_4__ r_reply_info; int /*<<< orphan*/ * r_pagelist; int /*<<< orphan*/  r_dentry_unless; TYPE_2__ r_args; int /*<<< orphan*/  r_req_flags; struct inode* r_parent; int /*<<< orphan*/  r_dentry; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_fs_client {struct ceph_mds_client* mdsc; } ;
struct ceph_acl_sec_ctx {int /*<<< orphan*/ * pagelist; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_7__ {int /*<<< orphan*/  is_dentry; } ;

/* Variables and functions */
 int CEPH_CAP_AUTH_EXCL ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_EXCL ; 
 int CEPH_CAP_FILE_SHARED ; 
 int /*<<< orphan*/  CEPH_MDS_OP_MKNOD ; 
 int /*<<< orphan*/  CEPH_MDS_R_PARENT_LOCKED ; 
 scalar_t__ CEPH_NOSNAP ; 
 int EDQUOT ; 
 int EROFS ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int PTR_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  USE_AUTH_MDS ; 
 int ceph_handle_notrace_create (struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  ceph_init_inode_acls (int /*<<< orphan*/ ,struct ceph_acl_sec_ctx*) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,struct inode*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 int ceph_pre_init_acls (struct inode*,int /*<<< orphan*/ *,struct ceph_acl_sec_ctx*) ; 
 scalar_t__ ceph_quota_is_max_files_exceeded (struct inode*) ; 
 int /*<<< orphan*/  ceph_release_acl_sec_ctx (struct ceph_acl_sec_ctx*) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int ceph_security_init_secctx (struct dentry*,int /*<<< orphan*/ ,struct ceph_acl_sec_ctx*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 void* cpu_to_le32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct dentry*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_mknod(struct inode *dir, struct dentry *dentry,
		      umode_t mode, dev_t rdev)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(dir->i_sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req;
	struct ceph_acl_sec_ctx as_ctx = {};
	int err;

	if (ceph_snap(dir) != CEPH_NOSNAP)
		return -EROFS;

	if (ceph_quota_is_max_files_exceeded(dir)) {
		err = -EDQUOT;
		goto out;
	}

	err = ceph_pre_init_acls(dir, &mode, &as_ctx);
	if (err < 0)
		goto out;
	err = ceph_security_init_secctx(dentry, mode, &as_ctx);
	if (err < 0)
		goto out;

	dout("mknod in dir %p dentry %p mode 0%ho rdev %d\n",
	     dir, dentry, mode, rdev);
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_MKNOD, USE_AUTH_MDS);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto out;
	}
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_args.mknod.mode = cpu_to_le32(mode);
	req->r_args.mknod.rdev = cpu_to_le32(rdev);
	req->r_dentry_drop = CEPH_CAP_FILE_SHARED | CEPH_CAP_AUTH_EXCL;
	req->r_dentry_unless = CEPH_CAP_FILE_EXCL;
	if (as_ctx.pagelist) {
		req->r_pagelist = as_ctx.pagelist;
		as_ctx.pagelist = NULL;
	}
	err = ceph_mdsc_do_request(mdsc, dir, req);
	if (!err && !req->r_reply_info.head->is_dentry)
		err = ceph_handle_notrace_create(dir, dentry);
	ceph_mdsc_put_request(req);
out:
	if (!err)
		ceph_init_inode_acls(d_inode(dentry), &as_ctx);
	else
		d_drop(dentry);
	ceph_release_acl_sec_ctx(&as_ctx);
	return err;
}