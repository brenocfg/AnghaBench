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
struct ceph_mds_request {int r_num_caps; int r_old_inode_drop; TYPE_2__ r_reply_info; int /*<<< orphan*/  r_inode_drop; void* r_dentry_unless; void* r_dentry_drop; void* r_old_dentry_unless; void* r_old_dentry_drop; int /*<<< orphan*/  r_req_flags; struct inode* r_parent; struct inode* r_old_dentry_dir; void* r_old_dentry; void* r_dentry; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_fs_client {struct ceph_mds_client* mdsc; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_dentry; } ;

/* Variables and functions */
 void* CEPH_CAP_FILE_EXCL ; 
 void* CEPH_CAP_FILE_SHARED ; 
 int CEPH_CAP_LINK_EXCL ; 
 int CEPH_CAP_LINK_SHARED ; 
 int CEPH_MDS_OP_RENAME ; 
 int CEPH_MDS_OP_RENAMESNAP ; 
 int /*<<< orphan*/  CEPH_MDS_R_PARENT_LOCKED ; 
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ CEPH_SNAPDIR ; 
 int EINVAL ; 
 int EROFS ; 
 int EXDEV ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int PTR_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  USE_AUTH_MDS ; 
 int /*<<< orphan*/  ceph_drop_caps_for_unlink (int /*<<< orphan*/ ) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,struct inode*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_quota_is_same_realm (struct inode*,struct inode*) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 scalar_t__ d_really_is_positive (struct dentry*) ; 
 void* dget (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct dentry*,struct inode*,struct dentry*) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_rename(struct inode *old_dir, struct dentry *old_dentry,
		       struct inode *new_dir, struct dentry *new_dentry,
		       unsigned int flags)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(old_dir->i_sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req;
	int op = CEPH_MDS_OP_RENAME;
	int err;

	if (flags)
		return -EINVAL;

	if (ceph_snap(old_dir) != ceph_snap(new_dir))
		return -EXDEV;
	if (ceph_snap(old_dir) != CEPH_NOSNAP) {
		if (old_dir == new_dir && ceph_snap(old_dir) == CEPH_SNAPDIR)
			op = CEPH_MDS_OP_RENAMESNAP;
		else
			return -EROFS;
	}
	/* don't allow cross-quota renames */
	if ((old_dir != new_dir) &&
	    (!ceph_quota_is_same_realm(old_dir, new_dir)))
		return -EXDEV;

	dout("rename dir %p dentry %p to dir %p dentry %p\n",
	     old_dir, old_dentry, new_dir, new_dentry);
	req = ceph_mdsc_create_request(mdsc, op, USE_AUTH_MDS);
	if (IS_ERR(req))
		return PTR_ERR(req);
	ihold(old_dir);
	req->r_dentry = dget(new_dentry);
	req->r_num_caps = 2;
	req->r_old_dentry = dget(old_dentry);
	req->r_old_dentry_dir = old_dir;
	req->r_parent = new_dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_old_dentry_drop = CEPH_CAP_FILE_SHARED;
	req->r_old_dentry_unless = CEPH_CAP_FILE_EXCL;
	req->r_dentry_drop = CEPH_CAP_FILE_SHARED;
	req->r_dentry_unless = CEPH_CAP_FILE_EXCL;
	/* release LINK_RDCACHE on source inode (mds will lock it) */
	req->r_old_inode_drop = CEPH_CAP_LINK_SHARED | CEPH_CAP_LINK_EXCL;
	if (d_really_is_positive(new_dentry)) {
		req->r_inode_drop =
			ceph_drop_caps_for_unlink(d_inode(new_dentry));
	}
	err = ceph_mdsc_do_request(mdsc, old_dir, req);
	if (!err && !req->r_reply_info.head->is_dentry) {
		/*
		 * Normally d_move() is done by fill_trace (called by
		 * do_request, above).  If there is no trace, we need
		 * to do it here.
		 */
		d_move(old_dentry, new_dentry);
	}
	ceph_mdsc_put_request(req);
	return err;
}