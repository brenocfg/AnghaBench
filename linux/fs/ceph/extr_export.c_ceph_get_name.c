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
struct dentry {int dummy; } ;
struct ceph_mds_reply_info_parsed {size_t dname_len; int /*<<< orphan*/  dname; } ;
struct ceph_mds_request {int r_num_caps; struct ceph_mds_reply_info_parsed r_reply_info; int /*<<< orphan*/  r_req_flags; void* r_parent; int /*<<< orphan*/  r_ino2; struct inode* r_inode; } ;
struct ceph_mds_client {int dummy; } ;
struct TYPE_2__ {struct ceph_mds_client* mdsc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_MDS_OP_LOOKUPNAME ; 
 int /*<<< orphan*/  CEPH_MDS_R_PARENT_LOCKED ; 
 scalar_t__ CEPH_NOSNAP ; 
 scalar_t__ IS_ERR (struct ceph_mds_request*) ; 
 int PTR_ERR (struct ceph_mds_request*) ; 
 int /*<<< orphan*/  USE_ANY_MDS ; 
 int __get_snap_name (struct dentry*,char*,struct dentry*) ; 
 TYPE_1__* ceph_inode_to_client (struct inode*) ; 
 struct ceph_mds_request* ceph_mdsc_create_request (struct ceph_mds_client*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ceph_mdsc_do_request (struct ceph_mds_client*,int /*<<< orphan*/ *,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  ceph_mdsc_put_request (struct ceph_mds_request*) ; 
 scalar_t__ ceph_snap (struct inode*) ; 
 int /*<<< orphan*/  ceph_vino (void*) ; 
 int /*<<< orphan*/  ceph_vinop (struct inode*) ; 
 void* d_inode (struct dentry*) ; 
 int /*<<< orphan*/  dout (char*,struct dentry*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  ihold (struct inode*) ; 
 int /*<<< orphan*/  inode_lock (void*) ; 
 int /*<<< orphan*/  inode_unlock (void*) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ceph_get_name(struct dentry *parent, char *name,
			 struct dentry *child)
{
	struct ceph_mds_client *mdsc;
	struct ceph_mds_request *req;
	struct inode *inode = d_inode(child);
	int err;

	if (ceph_snap(inode) != CEPH_NOSNAP)
		return __get_snap_name(parent, name, child);

	mdsc = ceph_inode_to_client(inode)->mdsc;
	req = ceph_mdsc_create_request(mdsc, CEPH_MDS_OP_LOOKUPNAME,
				       USE_ANY_MDS);
	if (IS_ERR(req))
		return PTR_ERR(req);

	inode_lock(d_inode(parent));

	req->r_inode = inode;
	ihold(inode);
	req->r_ino2 = ceph_vino(d_inode(parent));
	req->r_parent = d_inode(parent);
	set_bit(CEPH_MDS_R_PARENT_LOCKED, &req->r_req_flags);
	req->r_num_caps = 2;
	err = ceph_mdsc_do_request(mdsc, NULL, req);

	inode_unlock(d_inode(parent));

	if (!err) {
		struct ceph_mds_reply_info_parsed *rinfo = &req->r_reply_info;
		memcpy(name, rinfo->dname, rinfo->dname_len);
		name[rinfo->dname_len] = 0;
		dout("get_name %p ino %llx.%llx name %s\n",
		     child, ceph_vinop(inode), name);
	} else {
		dout("get_name %p ino %llx.%llx err %d\n",
		     child, ceph_vinop(inode), err);
	}

	ceph_mdsc_put_request(req);
	return err;
}