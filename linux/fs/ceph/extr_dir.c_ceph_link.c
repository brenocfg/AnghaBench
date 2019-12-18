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
struct ceph_mds_request {int r_num_caps; int r_old_inode_drop; TYPE_2__ r_reply_info; int /*<<< orphan*/  r_dentry_unless; int /*<<< orphan*/  r_dentry_drop; int /*<<< orphan*/  r_req_flags; struct inode* r_parent; void* r_old_dentry; void* r_dentry; } ;
struct ceph_mds_client {int dummy; } ;
struct ceph_fs_client {struct ceph_mds_client* mdsc; } ;
struct TYPE_3__ {int /*<<< orphan*/  is_dentry; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_FILE_EXCL ; 
 int /*<<< orphan*/  CEPH_CAP_FILE_SHARED ; 
 int CEPH_CAP_LINK_EXCL ; 
 int CEPH_CAP_LINK_SHARED ; 
 int /*<<< orphan*/  CEPH_MDS_OP_LINK ; 
 int /*<<< orphan*/  CEPH_MDS_R_PARENT_LOCKED ; 
 scalar_t__ CEPH_NOSNAP ; 
 int EROFS ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int PTR_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  USE_AUTH_MDS ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,struct inode*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 struct ceph_fs_client* ceph_sb_to_client (int /*<<< orphan*/ ) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_inode (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,int /*<<< orphan*/ ) ; 
 void* dget (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct inode*,struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  ihold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_link(struct dentry *old_dentry, struct inode *dir,
		     struct dentry *dentry)
{
	struct ceph_fs_client *fsc = ceph_sb_to_client(dir->i_sb);
	struct ceph_mds_client *mdsc = fsc->mdsc;
	struct ceph_mds_request *req;
	int err;

	if (ceph_snap(dir) != CEPH_NOSNAP)
		return -EROFS;

	dout("link in dir %p old_dentry %p dentry %p\n", dir,
	     old_dentry, dentry);
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_LINK, USE_AUTH_MDS);
	if (IS_ERR(req)) {
		d_drop(dentry);
		return PTR_ERR(req);
	}
	req->r_dentry = dget(dentry);
	req->r_num_caps = 2;
	req->r_old_dentry = dget(old_dentry);
	req->r_parent = dir;
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_dentry_drop = CEPH_CAP_FILE_SHARED;
	req->r_dentry_unless = CEPH_CAP_FILE_EXCL;
	/* release LINK_SHARED on source inode (mds will lock it) */
	req->r_old_inode_drop = CEPH_CAP_LINK_SHARED | CEPH_CAP_LINK_EXCL;
	err = ceph_mdsc_do_request(mdsc, dir, req);
	if (err) {
		d_drop(dentry);
	} else if (!req->r_reply_info.head->is_dentry) {
		ihold(d_inode(old_dentry));
		d_instantiate(dentry, d_inode(old_dentry));
	}
	ceph_mdsc_put_request(req);
	return err;
}