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
struct inode {int dummy; } ;
struct ceph_mds_request {int r_err; scalar_t__ r_old_dentry_dir; scalar_t__ r_parent; scalar_t__ r_inode; } ;
struct ceph_mds_client {int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CEPH_CAP_PIN ; 
 int /*<<< orphan*/  __do_request (struct ceph_mds_client*,struct ceph_mds_request*) ; 
 int /*<<< orphan*/  __register_request (struct ceph_mds_client*,struct ceph_mds_request*,struct inode*) ; 
 int /*<<< orphan*/  ceph_get_cap_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ceph_inode (scalar_t__) ; 
 int /*<<< orphan*/  dout (char*,struct ceph_mds_request*,struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int ceph_mdsc_submit_request(struct ceph_mds_client *mdsc, struct inode *dir,
			      struct ceph_mds_request *req)
{
	int err;

	/* take CAP_PIN refs for r_inode, r_parent, r_old_dentry */
	if (req->r_inode)
		ceph_get_cap_refs(ceph_inode(req->r_inode), CEPH_CAP_PIN);
	if (req->r_parent)
		ceph_get_cap_refs(ceph_inode(req->r_parent), CEPH_CAP_PIN);
	if (req->r_old_dentry_dir)
		ceph_get_cap_refs(ceph_inode(req->r_old_dentry_dir),
				  CEPH_CAP_PIN);

	dout("submit_request on %p for inode %p\n", req, dir);
	mutex_lock(&mdsc->mutex);
	__register_request(mdsc, req, dir);
	__do_request(mdsc, req);
	err = req->r_err;
	mutex_unlock(&mdsc->mutex);
	return err;
}