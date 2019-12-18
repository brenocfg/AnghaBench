#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct dentry {int dummy; } ;
struct TYPE_4__ {TYPE_1__* head; } ;
struct ceph_mds_request {int r_num_caps; int r_dentry_drop; TYPE_2__ r_reply_info; int /*<<< orphan*/  r_dentry_unless; int /*<<< orphan*/  r_dentry; int /*<<< orphan*/  r_req_flags; struct inode* r_parent; int /*<<< orphan*/  r_path2; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_fs_client {struct ceph_mds_client* mdsc; } ;
struct ceph_acl_sec_ctx {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_dentry; } ;

/* Variables and functions */
 int CEPH_CAP_AUTH_EXCL ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_EXCL ; 
 int CEPH_CAP_FILE_SHARED ; 
 int /*<<< orphan*/  CEPH_MDS_OP_SYMLINK ; 
 int /*<<< orphan*/  CEPH_MDS_R_PARENT_LOCKED ; 
 scalar_t__ CEPH_NOSNAP ; 
 int EDQUOT ; 
 int ENOMEM ; 
 int EROFS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int PTR_ERR (struct ceph_mds_request*) ; 
 int S_IFLNK ; 
 int /*<<< orphan*/  USE_AUTH_MDS ; 
 int ceph_handle_notrace_create (struct inode*,struct dentry*) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,struct inode*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 scalar_t__ ceph_quota_is_max_files_exceeded (struct inode*) ; 
 int /*<<< orphan*/  ceph_release_acl_sec_ctx (struct ceph_acl_sec_ctx*) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 int ceph_security_init_secctx (struct dentry*,int,struct ceph_acl_sec_ctx*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  dget (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct dentry*,char const*) ; 
 int /*<<< orphan*/  kstrdup (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_symlink(struct inode *dir, struct dentry *dentry,
			    const char *dest)
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

	err = ceph_security_init_secctx(dentry, S_IFLNK | 0777, &as_ctx);
	if (err < 0)
		goto out;

	dout("symlink in dir %p dentry %p to '%s'\n", dir, dentry, dest);
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_SYMLINK, USE_AUTH_MDS);
	if (IS_ERR(req)) {
		err = PTR_ERR(req);
		goto out;
	}
	req->r_path2 = kstrdup(dest, GFP_KERNEL);
	if (!req->r_path2) {
		err = -ENOMEM;
		ceph_mdsc_put_request(req);
		goto out;
	}
	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	req->r_dentry_drop = CEPH_CAP_FILE_SHARED | CEPH_CAP_AUTH_EXCL;
	req->r_dentry_unless = CEPH_CAP_FILE_EXCL;
	err = ceph_mdsc_do_request(mdsc, dir, req);
	if (!err && !req->r_reply_info.head->is_dentry)
		err = ceph_handle_notrace_create(dir, dentry);
	ceph_mdsc_put_request(req);
out:
	if (err)
		d_drop(dentry);
	ceph_release_acl_sec_ctx(&as_ctx);
	return err;
}